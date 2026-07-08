/* ************************************************************************** */
/*                                                                            */
/*   Server.cpp - Implementation de la classe Server                          */
/*                                                                            */
/*   Contient la boucle principale (poll), la gestion des connexions,         */
/*   le systeme de buffer d'envoi, et les utilitaires du serveur.             */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sstream>
#include <csignal>

// Taille maximale du buffer de reception par client (protection contre le flood)
static const size_t MAX_BUFFER = 4096;

/* ========================================================================== */
/*   Constructeur / Destructeur                                               */
/* ========================================================================== */

Server::Server(int port, const std::string& password) : _port(port), _password(password), _listenFd(-1) {}

/*
** Destructeur : libere proprement toutes les ressources.
** - Ferme tous les fd clients et libere les objets Client
** - Libere tous les objets Channel
** - Ferme la socket d'ecoute
*/
Server::~Server() {
	for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
		close(it->first);
		delete it->second;
	}
	for (std::map<std::string, Channel*>::iterator it = _channels.begin(); it != _channels.end(); ++it)
		delete it->second;
	if (_listenFd >= 0)
		close(_listenFd);
}

/* ========================================================================== */
/*   Initialisation de la socket                                              */
/* ========================================================================== */

/*
** Cree et configure la socket d'ecoute du serveur :
** 1. Cree une socket TCP (AF_INET, SOCK_STREAM)
** 2. Active SO_REUSEADDR pour pouvoir relancer rapidement apres un crash
** 3. Met la socket en mode non-bloquant (O_NONBLOCK) via fcntl
** 4. Bind sur toutes les interfaces (INADDR_ANY) au port specifie
** 5. Commence a ecouter avec listen()
** 6. Ajoute le fd au tableau poll avec POLLIN pour detecter les connexions
*/
void Server::_initSocket() {
	_listenFd = socket(AF_INET, SOCK_STREAM, 0);
	if (_listenFd < 0)
		throw std::runtime_error("socket() failed");

	// SO_REUSEADDR permet de reutiliser le port immediatement apres fermeture
	int opt = 1;
	if (setsockopt(_listenFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
		close(_listenFd);
		_listenFd = -1;
		throw std::runtime_error("setsockopt() failed");
	}

	// Mode non-bloquant : accept() retournera -1 au lieu de bloquer s'il n'y a pas de connexion
	if (fcntl(_listenFd, F_SETFL, O_NONBLOCK) < 0) {
		close(_listenFd);
		_listenFd = -1;
		throw std::runtime_error("fcntl() failed");
	}

	struct sockaddr_in addr;
	std::memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;  // Ecoute sur toutes les interfaces reseau
	addr.sin_port = htons(_port);        // Conversion en network byte order

	if (bind(_listenFd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
		close(_listenFd);
		_listenFd = -1;
		throw std::runtime_error("bind() failed");
	}
	if (listen(_listenFd, SOMAXCONN) < 0) {
		close(_listenFd);
		_listenFd = -1;
		throw std::runtime_error("listen() failed");
	}

	// Ajout de la socket d'ecoute au tableau poll (premier element)
	struct pollfd pfd;
	pfd.fd = _listenFd;
	pfd.events = POLLIN;
	pfd.revents = 0;
	_pollfds.push_back(pfd);
	std::cout << "Server listening on port " << _port << std::endl;
}

/* ========================================================================== */
/*   Boucle principale                                                        */
/* ========================================================================== */

// Variable globale pour l'arret propre via signal (SIGINT/SIGTERM)
static volatile bool g_running = true;

static void signalHandler(int) { g_running = false; }

/*
** Boucle principale du serveur :
** 1. Initialise la socket et les handlers de signaux
** 2. Appelle poll() qui bloque jusqu'a ce qu'un evenement se produise
** 3. Pour chaque fd avec un evenement :
**    - Si c'est la socket d'ecoute + POLLIN : accepte une nouvelle connexion
**    - Si c'est un client + POLLERR/POLLHUP : marque pour deconnexion
**    - Si c'est un client + POLLOUT : envoie les donnees en attente
**    - Si c'est un client + POLLIN : lit les donnees recues
** 4. Flush les deconnexions en attente
** 5. Met a jour les events poll (ajoute POLLOUT si un client a des donnees a envoyer)
**
** IMPORTANT : On prend un snapshot du tableau _pollfds avant d'iterer car
** les operations (accept, remove) peuvent modifier le tableau pendant l'iteration.
*/
void Server::run() {
	_initSocket();

	// Configuration des handlers de signaux pour arret propre (Ctrl+C)
	struct sigaction sa;
	sa.sa_handler = signalHandler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	::sigaction(SIGINT, &sa, NULL);
	::sigaction(SIGTERM, &sa, NULL);

	while (g_running) {
		// poll() est l'UNIQUE point de multiplexage I/O du serveur
		// Il surveille tous les fd (ecoute + clients) et bloque jusqu'a un evenement
		int ret = poll(&_pollfds[0], _pollfds.size(), -1);
		if (ret < 0) {
			if (!g_running) break;  // Interrompu par un signal
			continue;
		}

		// Snapshot pour eviter les problemes si _pollfds est modifie pendant l'iteration
		std::vector<struct pollfd> snapshot(_pollfds);
		for (size_t i = 0; i < snapshot.size(); i++) {
			int fd = snapshot[i].fd;
			short rev = snapshot[i].revents;
			if (!rev) continue;

			// Socket d'ecoute : une nouvelle connexion est en attente
			if (fd == _listenFd) {
				if (rev & POLLIN)
					_acceptClient();
				continue;
			}

			// Client : erreur ou deconnexion detectee par poll
			if (rev & (POLLERR | POLLHUP | POLLNVAL)) {
				_toRemove.insert(fd);
				continue;
			}

			// Client : pret a recevoir des donnees (buffer kernel a de la place)
			// On envoie les messages en attente dans le _sendBuffer du client
			if (rev & POLLOUT) {
				_sendData(fd);
			}

			// Client : des donnees sont disponibles en lecture
			if (rev & POLLIN) {
				if (_clients.find(fd) != _clients.end())
					_receiveData(fd);
			}
		}

		// Deconnecte tous les clients marques pour suppression
		_flushRemovals();

		/*
		** Mise a jour des events poll pour le prochain cycle :
		** - Si un client a des donnees en attente dans son _sendBuffer,
		**   on ajoute POLLOUT pour que poll() nous signale quand on peut envoyer
		** - Sinon on ne surveille que POLLIN (reception)
		** On commence a i=1 car i=0 est la socket d'ecoute
		*/
		for (size_t i = 1; i < _pollfds.size(); i++) {
			std::map<int, Client*>::iterator cit = _clients.find(_pollfds[i].fd);
			if (cit != _clients.end() && cit->second->hasPendingData())
				_pollfds[i].events = POLLIN | POLLOUT;
			else
				_pollfds[i].events = POLLIN;
		}
	}
	std::cout << "\nServer shutting down." << std::endl;
}

/* ========================================================================== */
/*   Gestion des connexions                                                   */
/* ========================================================================== */

/*
** Accepte une nouvelle connexion entrante :
** 1. accept() retourne un nouveau fd pour ce client
** 2. On met ce fd en non-bloquant
** 3. On cree un objet Client et on stocke son IP
** 4. On ajoute le fd au tableau poll avec POLLIN
*/
void Server::_acceptClient() {
	struct sockaddr_in addr;
	socklen_t len = sizeof(addr);
	int fd = accept(_listenFd, (struct sockaddr*)&addr, &len);
	if (fd < 0) return;

	// Le fd client doit aussi etre non-bloquant
	if (fcntl(fd, F_SETFL, O_NONBLOCK) < 0) {
		close(fd);
		return;
	}

	Client* client;
	try {
		client = new Client(fd);
	} catch (...) {
		close(fd);
		return;
	}
	client->setHost(inet_ntoa(addr.sin_addr));
	_clients[fd] = client;

	struct pollfd pfd;
	pfd.fd = fd;
	pfd.events = POLLIN;
	pfd.revents = 0;
	_pollfds.push_back(pfd);
	std::cout << "New connection from " << client->getHost() << " (fd " << fd << ")" << std::endl;
}

/* ========================================================================== */
/*   Reception et traitement des donnees                                      */
/* ========================================================================== */

/*
** Lit les donnees disponibles sur un fd client :
** 1. recv() lit ce qui est disponible (max 511 octets)
** 2. Si recv retourne 0 ou -1 : le client est deconnecte
** 3. Les donnees sont ajoutees au buffer de reception du client
** 4. On verifie que le buffer ne depasse pas MAX_BUFFER (anti-flood)
** 5. On extrait et traite chaque ligne complete (terminee par \r\n ou \n)
**
** Le mecanisme de buffer permet de gerer les commandes partielles :
** si un client envoie "PRI" puis "VMSG #chan :hello\r\n" en deux paquets,
** le buffer accumule les deux et extractLine() retourne la ligne complete.
*/
void Server::_receiveData(int fd) {
	char buf[512];
	int bytes = recv(fd, buf, sizeof(buf) - 1, 0);
	if (bytes <= 0) {
		_toRemove.insert(fd);
		return;
	}
	buf[bytes] = '\0';
	Client* client = _clients[fd];
	client->appendBuffer(buf);

	// Protection contre le flood : si le buffer depasse 4Ko, on deconnecte
	if (client->getBuffer().length() > MAX_BUFFER) {
		_sendReply(client, "ERROR :Input buffer overflow\r\n");
		_toRemove.insert(fd);
		return;
	}

	// Extraction et traitement de chaque ligne complete
	std::string line;
	while (!(line = client->extractLine()).empty()) {
		_processLine(client, line);
		// Si QUIT a ete appele, on arrete de traiter les lignes restantes
		if (_toRemove.count(fd))
			break;
	}
}

/*
** Parse une ligne IRC et dispatch vers la commande appropriee.
**
** Format IRC : [:<prefix>] <commande> [<args>...] [:<trailing>]
** - Le prefix (optionnel) commence par ':' et est ignore cote serveur
** - La commande est le premier mot apres le prefix
** - Les arguments sont separes par des espaces
** - Le dernier argument peut commencer par ':' pour contenir des espaces
**   (ex: "PRIVMSG #chan :Hello World" -> args = ["#chan", "Hello World"])
**
** Ordre d'enregistrement requis : PASS -> NICK -> USER
** Tant que le client n'est pas registered, seuls PASS/NICK/USER/QUIT sont acceptes.
*/
void Server::_processLine(Client* client, const std::string& line) {
	if (line.empty()) return;

	std::string rest = line;

	// Ignore le prefix s'il est present (commence par ':')
	if (rest[0] == ':') {
		size_t sp = rest.find(' ');
		if (sp == std::string::npos) return;
		rest = rest.substr(sp + 1);
	}

	// Parsing des arguments IRC
	std::vector<std::string> args;
	while (!rest.empty()) {
		// Un argument commencant par ':' = trailing (tout le reste est un seul argument)
		if (rest[0] == ':') {
			args.push_back(rest.substr(1));
			break;
		}
		size_t sp = rest.find(' ');
		if (sp == std::string::npos) {
			args.push_back(rest);
			break;
		}
		args.push_back(rest.substr(0, sp));
		rest = rest.substr(sp + 1);
	}
	if (args.empty()) return;

	// La commande est le premier element, convertie en majuscules
	std::string cmd = _toUpper(args[0]);
	args.erase(args.begin());

	// CAP est envoye par les clients modernes, on l'ignore silencieusement
	if (cmd == "CAP") return;

	// Dispatch des commandes
	if (cmd == "PASS") _cmdPass(client, args);
	else if (cmd == "NICK") _cmdNick(client, args);
	else if (cmd == "USER") _cmdUser(client, args);
	else if (cmd == "QUIT") _cmdQuit(client, args);
	else if (!client->isRegistered())
		_sendReply(client, ":ircserv 451 * :You have not registered\r\n");
	else if (cmd == "JOIN") _cmdJoin(client, args);
	else if (cmd == "PART") _cmdPart(client, args);
	else if (cmd == "PRIVMSG") _cmdPrivmsg(client, args);
	else if (cmd == "KICK") _cmdKick(client, args);
	else if (cmd == "INVITE") _cmdInvite(client, args);
	else if (cmd == "TOPIC") _cmdTopic(client, args);
	else if (cmd == "MODE") _cmdMode(client, args);
	else if (cmd == "PING") _cmdPing(client, args);
	else
		_sendReply(client, ":ircserv 421 " + client->getNick() + " " + cmd + " :Unknown command\r\n");
}

/* ========================================================================== */
/*   Deconnexion des clients                                                  */
/* ========================================================================== */

/*
** Deconnecte un client proprement :
** 1. Notifie tous les channels ou il etait present (QUIT broadcast)
** 2. Le retire de chaque channel (et supprime les channels vides)
** 3. Ferme le fd, libere la memoire, retire du tableau poll
*/
void Server::_removeClient(int fd) {
	std::map<int, Client*>::iterator cit = _clients.find(fd);
	if (cit == _clients.end()) return;

	std::cout << "Client disconnected (fd " << fd << ")" << std::endl;
	Client* client = cit->second;

	// Retire le client de tous les channels et notifie les autres membres
	for (std::map<std::string, Channel*>::iterator it = _channels.begin(); it != _channels.end();) {
		if (it->second->isMember(client)) {
			it->second->broadcast(":" + client->getPrefix() + " QUIT :Leaving\r\n", client);
			it->second->removeMember(client);
		}
		// Si le channel est vide apres le depart, on le supprime
		if (it->second->memberCount() == 0) {
			delete it->second;
			_channels.erase(it++);
		} else
			++it;
	}

	close(fd);
	delete client;
	_clients.erase(cit);

	// Retire le fd du tableau poll
	for (size_t i = 0; i < _pollfds.size(); i++) {
		if (_pollfds[i].fd == fd) {
			_pollfds.erase(_pollfds.begin() + i);
			break;
		}
	}
}

/* Parcourt le set _toRemove et deconnecte chaque client marque */
void Server::_flushRemovals() {
	for (std::set<int>::iterator it = _toRemove.begin(); it != _toRemove.end(); ++it)
		_removeClient(*it);
	_toRemove.clear();
}

/* ========================================================================== */
/*   Systeme de buffer d'envoi (POLLOUT)                                      */
/* ========================================================================== */

/*
** Enqueue un message dans le buffer d'envoi du client.
** Le message ne sera PAS envoye immediatement : il sera envoye au prochain
** cycle poll() quand POLLOUT est signale sur ce fd.
** Cela garantit le respect de la regle : "poll() avant chaque send()".
*/
void Server::_sendReply(Client* client, const std::string& msg) {
	client->queueMessage(msg);
	_updatePollEvents(client->getFd());
}

/*
** Met a jour les events poll d'un fd specifique :
** - Ajoute POLLOUT si le client a des donnees en attente d'envoi
** - Retire POLLOUT si le buffer d'envoi est vide
*/
void Server::_updatePollEvents(int fd) {
	for (size_t i = 0; i < _pollfds.size(); i++) {
		if (_pollfds[i].fd == fd) {
			std::map<int, Client*>::iterator it = _clients.find(fd);
			if (it != _clients.end() && it->second->hasPendingData())
				_pollfds[i].events = POLLIN | POLLOUT;
			else
				_pollfds[i].events = POLLIN;
			break;
		}
	}
}

/*
** Appele quand poll() signale POLLOUT sur un fd client.
** Tente de flush le buffer d'envoi du client.
** Si send() echoue (client deconnecte), on marque le fd pour suppression.
**
** C'est ici que le send() reel a lieu, APRES que poll() ait confirme
** que le fd est pret en ecriture. Cela resout le probleme du client
** stoppe (^Z) : les messages s'accumulent dans le buffer et sont
** envoyes quand le client revient (le buffer kernel TCP se libere).
*/
void Server::_sendData(int fd) {
	std::map<int, Client*>::iterator it = _clients.find(fd);
	if (it == _clients.end()) return;
	if (!it->second->flushSendBuffer())
		_toRemove.insert(fd);
	_updatePollEvents(fd);
}

/* ========================================================================== */
/*   Utilitaires                                                              */
/* ========================================================================== */

/* Recherche un client par son nickname (parcours lineaire de la map) */
Client* Server::_findClientByNick(const std::string& nick) {
	for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
		if (it->second->getNick() == nick)
			return it->second;
	return NULL;
}

/* Retourne un channel existant ou en cree un nouveau */
Channel* Server::_getOrCreateChannel(const std::string& name) {
	std::map<std::string, Channel*>::iterator it = _channels.find(name);
	if (it != _channels.end())
		return it->second;
	Channel* ch = new Channel(name);
	_channels[name] = ch;
	return ch;
}

/* Envoie les messages de bienvenue IRC (RPL 001 a 004) apres enregistrement */
void Server::_welcomeClient(Client* c) {
	std::string nick = c->getNick();
	_sendReply(c, ":ircserv 001 " + nick + " :Welcome to the IRC server, " + c->getPrefix() + "\r\n");
	_sendReply(c, ":ircserv 002 " + nick + " :Your host is ircserv, running version 1.0\r\n");
	_sendReply(c, ":ircserv 003 " + nick + " :This server was created today\r\n");
	_sendReply(c, ":ircserv 004 " + nick + " ircserv 1.0 o itkol\r\n");
}

/* Split une string par un caractere delimiteur, ignore les tokens vides */
std::vector<std::string> Server::_split(const std::string& s, char delim) {
	std::vector<std::string> tokens;
	std::istringstream iss(s);
	std::string token;
	while (std::getline(iss, token, delim))
		if (!token.empty())
			tokens.push_back(token);
	return tokens;
}

/* Convertit une string en majuscules (pour comparer les commandes IRC) */
std::string Server::_toUpper(const std::string& s) {
	std::string r = s;
	for (size_t i = 0; i < r.length(); i++)
		r[i] = std::toupper(r[i]);
	return r;
}
