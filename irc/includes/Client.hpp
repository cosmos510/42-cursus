/* ************************************************************************** */
/*                                                                            */
/*   Client.hpp - Represente un client connecte au serveur IRC                */
/*                                                                            */
/*   Chaque client possede :                                                  */
/*   - Un buffer de reception (_buffer) pour accumuler les donnees recues     */
/*     jusqu'a former une ligne complete (terminee par \r\n ou \n)            */
/*   - Un buffer d'envoi (_sendBuffer) pour stocker les messages a envoyer    */
/*     en attente que poll() signale POLLOUT                                  */
/*   - Les informations d'identite IRC (nick, user, realname, host)          */
/*   - L'etat d'enregistrement (passwd + nick + user = registered)           */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>

class Client {
public:
	Client(int fd);
	~Client();

	/* --- Getters --- */
	int getFd() const;
	std::string getNick() const;
	std::string getUser() const;
	std::string getRealname() const;
	std::string getHost() const;

	/* Retourne le prefix IRC complet : nick!user@host */
	std::string getPrefix() const;

	/* Retourne une reference au buffer de reception (pour verifier sa taille) */
	std::string& getBuffer();

	/*
	** Un client est considere comme "registered" (enregistre) quand il a
	** complete les 3 etapes : PASS + NICK + USER. Avant ca, seules les
	** commandes PASS, NICK, USER et QUIT sont autorisees.
	*/
	bool isRegistered() const;
	bool hasPasswd() const;
	bool hasNick() const;
	bool hasUser() const;

	/* --- Setters --- */
	void setNick(const std::string& nick);
	void setUser(const std::string& user);
	void setRealname(const std::string& realname);
	void setHost(const std::string& host);
	void setPasswd(bool val);

	/* --- Buffer de reception --- */

	/* Ajoute les donnees brutes recues par recv() au buffer */
	void appendBuffer(const std::string& data);

	/*
	** Extrait la premiere ligne complete du buffer (terminee par \r\n ou \n).
	** Retourne une string vide si aucune ligne complete n'est disponible.
	** C'est ce mecanisme qui permet de gerer les commandes partielles :
	** les donnees restent dans le buffer jusqu'a reception du \r\n.
	*/
	std::string extractLine();

	/* --- Buffer d'envoi --- */

	/*
	** Ajoute un message au buffer d'envoi. Le message sera envoye
	** au prochain cycle poll() quand POLLOUT est signale sur ce fd.
	** Cela evite tout appel a send() sans verification prealable par poll().
	*/
	void queueMessage(const std::string& msg);

	/* Retourne true si le buffer d'envoi contient des donnees en attente */
	bool hasPendingData() const;

	/*
	** Tente d'envoyer le contenu du buffer d'envoi via send().
	** send() en mode non-bloquant peut n'envoyer qu'une partie des donnees
	** (si le buffer kernel TCP est partiellement plein), d'ou l'erase partiel.
	** Retourne false si send() echoue (client deconnecte), true sinon.
	*/
	bool flushSendBuffer();

private:
	int _fd;                 // File descriptor de la socket client
	std::string _nick;       // Nickname IRC du client
	std::string _user;       // Username IRC du client
	std::string _realname;   // Nom reel du client
	std::string _host;       // Adresse IP du client
	std::string _buffer;     // Buffer de reception (donnees partielles en attente)
	std::string _sendBuffer; // Buffer d'envoi (messages en attente d'etre envoyes)
	bool _passwd;            // true si le client a envoye le bon PASS
	bool _nickSet;           // true si le client a defini un NICK
	bool _userSet;           // true si le client a envoye USER
};

#endif
