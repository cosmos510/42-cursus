/* ************************************************************************** */
/*                                                                            */
/*   Server.hpp - Classe principale du serveur IRC                            */
/*                                                                            */
/*   Cette classe gere l'ensemble du serveur : la socket d'ecoute,            */
/*   les connexions clients, les channels, et le dispatch des commandes IRC.  */
/*   Elle utilise poll() comme unique mecanisme de multiplexage I/O.          */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>
#include <vector>
#include <map>
#include <set>
#include <poll.h>
#include "Client.hpp"
#include "Channel.hpp"

class Server {
public:
	/* Constructeur : initialise le port et le mot de passe du serveur */
	Server(int port, const std::string& password);

	/* Destructeur : ferme toutes les connexions et libere la memoire */
	~Server();

	/* Boucle principale du serveur : initialise la socket puis boucle sur poll() */
	void run();

private:
	int _port;                                  // Port d'ecoute du serveur
	std::string _password;                      // Mot de passe requis pour se connecter
	int _listenFd;                              // File descriptor de la socket d'ecoute
	std::vector<struct pollfd> _pollfds;         // Tableau des fd surveilles par poll()
	std::map<int, Client*> _clients;            // Map fd -> Client* pour chaque connexion
	std::map<std::string, Channel*> _channels;  // Map nom -> Channel* pour chaque channel
	std::set<int> _toRemove;                    // Set des fd a deconnecter en fin de boucle

	/* Cree la socket d'ecoute, la configure en non-bloquant, bind et listen */
	void _initSocket();

	/* Accepte une nouvelle connexion entrante et cree le Client associe */
	void _acceptClient();

	/* Lit les donnees recues sur un fd client et extrait les lignes completes */
	void _receiveData(int fd);

	/*
	** Parse une ligne IRC brute et dispatch vers la commande appropriee.
	** Le parsing suit le protocole IRC : on ignore le prefix (si present),
	** on extrait la commande et les arguments (le dernier argument peut
	** commencer par ':' pour inclure des espaces).
	*/
	void _processLine(Client* client, const std::string& line);

	/* Deconnecte un client : le retire de tous les channels, ferme le fd, libere la memoire */
	void _removeClient(int fd);

	/* Parcourt _toRemove et appelle _removeClient pour chaque fd marque */
	void _flushRemovals();

	/*
	** Enqueue un message dans le buffer d'envoi du client.
	** Le message ne sera envoye qu'au prochain cycle poll() quand POLLOUT est signale.
	** Cela garantit qu'on ne fait jamais de send() sans avoir poll() avant.
	*/
	void _sendReply(Client* client, const std::string& msg);

	/* Met a jour les events poll() d'un fd : ajoute POLLOUT si le client a des donnees en attente */
	void _updatePollEvents(int fd);

	/* Recherche un client par son nickname dans la map _clients */
	Client* _findClientByNick(const std::string& nick);

	/* Retourne le channel s'il existe, sinon le cree */
	Channel* _getOrCreateChannel(const std::string& name);

	/* --- Commandes IRC --- */
	void _cmdPass(Client* c, std::vector<std::string>& args);    // Authentification par mot de passe
	void _cmdNick(Client* c, std::vector<std::string>& args);    // Definir/changer le nickname
	void _cmdUser(Client* c, std::vector<std::string>& args);    // Definir le username et realname
	void _cmdJoin(Client* c, std::vector<std::string>& args);    // Rejoindre un ou plusieurs channels
	void _cmdPart(Client* c, std::vector<std::string>& args);    // Quitter un ou plusieurs channels
	void _cmdPrivmsg(Client* c, std::vector<std::string>& args); // Envoyer un message prive ou sur un channel
	void _cmdKick(Client* c, std::vector<std::string>& args);    // Expulser un utilisateur d'un channel (op)
	void _cmdInvite(Client* c, std::vector<std::string>& args);  // Inviter un utilisateur dans un channel (op)
	void _cmdTopic(Client* c, std::vector<std::string>& args);   // Voir/modifier le topic d'un channel
	void _cmdMode(Client* c, std::vector<std::string>& args);    // Modifier les modes d'un channel (i/t/k/o/l)
	void _cmdQuit(Client* c, std::vector<std::string>& args);    // Deconnexion propre du client
	void _cmdPing(Client* c, std::vector<std::string>& args);    // Repondre PONG pour garder la connexion

	/*
	** Appele quand poll() signale POLLOUT sur un fd client.
	** Flush le buffer d'envoi du client vers le reseau.
	** Si send() echoue, le client est marque pour suppression.
	*/
	void _sendData(int fd);

	/* Envoie les messages de bienvenue IRC (001-004) apres enregistrement complet */
	void _welcomeClient(Client* c);

	/* Utilitaire : split une string par un delimiteur */
	static std::vector<std::string> _split(const std::string& s, char delim);

	/* Utilitaire : convertit une string en majuscules */
	static std::string _toUpper(const std::string& s);
};

#endif
