/* ************************************************************************** */
/*                                                                            */
/*   Client.cpp - Implementation de la classe Client                          */
/*                                                                            */
/*   Gere l'etat d'un client connecte : identite, buffers I/O,               */
/*   et etat d'enregistrement.                                                */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include <sys/socket.h>

/* Constructeur : initialise le fd et les flags a false */
Client::Client(int fd) : _fd(fd), _passwd(false), _nickSet(false), _userSet(false) {}

Client::~Client() {}

/* --- Getters simples --- */
int Client::getFd() const { return _fd; }
std::string Client::getNick() const { return _nick; }
std::string Client::getUser() const { return _user; }
std::string Client::getRealname() const { return _realname; }
std::string Client::getHost() const { return _host; }
std::string& Client::getBuffer() { return _buffer; }
bool Client::hasPasswd() const { return _passwd; }
bool Client::hasNick() const { return _nickSet; }
bool Client::hasUser() const { return _userSet; }

/*
** Un client est "registered" quand les 3 conditions sont remplies :
** 1. Il a envoye le bon mot de passe (PASS)
** 2. Il a defini un nickname (NICK)
** 3. Il a envoye ses infos utilisateur (USER)
** C'est seulement apres ca qu'il peut utiliser les commandes IRC.
*/
bool Client::isRegistered() const { return _passwd && _nickSet && _userSet; }

/*
** Retourne le prefix IRC du client au format : nick!user@host
** Ce prefix est utilise dans tous les messages envoyes aux autres clients
** pour identifier l'emetteur (ex: ":max!maxime@127.0.0.1 PRIVMSG #chan :hello")
*/
std::string Client::getPrefix() const {
	return _nick + "!" + _user + "@" + _host;
}

/* --- Setters --- */
void Client::setNick(const std::string& nick) { _nick = nick; _nickSet = true; }
void Client::setUser(const std::string& user) { _user = user; _userSet = true; }
void Client::setRealname(const std::string& realname) { _realname = realname; }
void Client::setHost(const std::string& host) { _host = host; }
void Client::setPasswd(bool val) { _passwd = val; }

/* ========================================================================== */
/*   Buffer de reception                                                      */
/* ========================================================================== */

/* Ajoute les donnees brutes recues par recv() au buffer */
void Client::appendBuffer(const std::string& data) { _buffer += data; }

/*
** Extrait la premiere ligne complete du buffer de reception.
**
** Le protocole IRC termine les messages par \r\n, mais certains clients
** (notamment nc) n'envoient que \n. On gere les deux cas.
**
** Fonctionnement :
** - Cherche \r\n dans le buffer, sinon cherche \n
** - Si trouve : extrait la ligne (sans le terminateur), l'efface du buffer
** - Si pas trouve : retourne "" (la commande est incomplete, on attend plus de donnees)
**
** Exemple avec commande partielle :
**   recv("PRIV")     -> buffer = "PRIV"         -> extractLine() = "" (pas de \r\n)
**   recv("MSG #c :hi\r\n") -> buffer = "PRIVMSG #c :hi\r\n" -> extractLine() = "PRIVMSG #c :hi"
*/
std::string Client::extractLine() {
	std::string::size_type pos = _buffer.find("\r\n");
	if (pos == std::string::npos)
		pos = _buffer.find("\n");
	if (pos == std::string::npos)
		return "";
	std::string line = _buffer.substr(0, pos);
	_buffer.erase(0, pos + (_buffer[pos] == '\r' ? 2 : 1));
	return line;
}

/* ========================================================================== */
/*   Buffer d'envoi                                                           */
/* ========================================================================== */

/* Ajoute un message au buffer d'envoi (sera envoye quand POLLOUT est signale) */
void Client::queueMessage(const std::string& msg) { _sendBuffer += msg; }

/* Retourne true si des donnees attendent d'etre envoyees */
bool Client::hasPendingData() const { return !_sendBuffer.empty(); }

/*
** Tente d'envoyer le contenu du buffer d'envoi via send().
**
** En mode non-bloquant, send() peut :
** - Envoyer tout le buffer d'un coup (cas normal)
** - N'envoyer qu'une partie (buffer kernel TCP partiellement plein)
**   -> on efface seulement ce qui a ete envoye, le reste sera envoye au prochain POLLOUT
** - Retourner -1 (erreur, client deconnecte) -> on retourne false
**
** Ce mecanisme est crucial pour le cas du client stoppe (^Z) :
** Quand un client est stoppe, son buffer TCP kernel se remplit.
** send() n'envoie que ce qui rentre, le reste reste dans _sendBuffer.
** Quand le client reprend, le buffer kernel se vide, POLLOUT est signale,
** et on peut envoyer le reste. Le serveur ne bloque jamais.
*/
bool Client::flushSendBuffer() {
	if (_sendBuffer.empty()) return true;
	ssize_t sent = send(_fd, _sendBuffer.c_str(), _sendBuffer.length(), 0);
	if (sent < 0) return false;
	_sendBuffer.erase(0, sent);
	return true;
}
