/* ************************************************************************** */
/*                                                                            */
/*   Commands.cpp - Implementation des commandes IRC                          */
/*                                                                            */
/*   Chaque commande suit le meme pattern :                                   */
/*   1. Verification des preconditions (enregistrement, parametres)           */
/*   2. Verification des permissions (operateur, membre du channel)           */
/*   3. Execution de la commande                                              */
/*   4. Envoi des reponses/notifications                                      */
/*                                                                            */
/*   Les codes numeriques (461, 403, etc.) sont les codes d'erreur IRC        */
/*   standards definis dans la RFC 2812.                                       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <sstream>
#include <cstdlib>

/* ========================================================================== */
/*   PASS - Authentification par mot de passe                                 */
/* ========================================================================== */

/*
** PASS <password>
** Premiere commande a envoyer pour s'authentifier.
** Le mot de passe doit correspondre a celui passe en argument au serveur.
** Doit etre envoye AVANT NICK et USER.
** Erreurs : 462 (deja enregistre), 461 (pas de parametre), 464 (mauvais mdp)
*/
void Server::_cmdPass(Client* c, std::vector<std::string>& args) {
	if (c->isRegistered())
		return _sendReply(c, ":ircserv 462 " + c->getNick() + " :You may not reregister\r\n");
	if (args.empty())
		return _sendReply(c, ":ircserv 461 * PASS :Not enough parameters\r\n");
	if (args[0] != _password)
		return _sendReply(c, ":ircserv 464 * :Password incorrect\r\n");
	c->setPasswd(true);
}

/* ========================================================================== */
/*   NICK - Definition/changement de nickname                                 */
/* ========================================================================== */

/*
** NICK <nickname>
** Definit ou change le nickname du client.
** Regles de validation :
** - Ne peut pas etre vide
** - Ne peut pas contenir : espace, virgule, *, ?, !, @, .
** - Ne peut pas commencer par # ou :
** - Doit etre unique sur le serveur
** - PASS doit avoir ete envoye avant
**
** Si le client change de nick apres enregistrement, on notifie avec l'ancien prefix.
** Si c'est le dernier element manquant pour l'enregistrement, on envoie le welcome.
*/
void Server::_cmdNick(Client* c, std::vector<std::string>& args) {
	if (args.empty())
		return _sendReply(c, ":ircserv 431 * :No nickname given\r\n");
	std::string nick = args[0];
	if (nick.empty() || nick.find_first_of(" ,*?!@.") != std::string::npos || nick[0] == '#' || nick[0] == ':')
		return _sendReply(c, ":ircserv 432 * " + nick + " :Erroneous nickname\r\n");
	if (_findClientByNick(nick) && _findClientByNick(nick) != c)
		return _sendReply(c, ":ircserv 433 * " + nick + " :Nickname is already in use\r\n");
	if (!c->hasPasswd())
		return _sendReply(c, ":ircserv 451 * :You have not registered (PASS required)\r\n");

	std::string oldPrefix = c->hasNick() ? c->getPrefix() : "";
	bool wasRegistered = c->isRegistered();
	c->setNick(nick);

	// Notifie le changement de nick si le client avait deja un nick
	if (!oldPrefix.empty())
		_sendReply(c, ":" + oldPrefix + " NICK " + nick + "\r\n");
	// Si l'enregistrement vient de se completer, envoie le welcome
	if (!wasRegistered && c->isRegistered())
		_welcomeClient(c);
}

/* ========================================================================== */
/*   USER - Definition du username et realname                                */
/* ========================================================================== */

/*
** USER <username> <mode> <unused> :<realname>
** Definit le username et le realname du client.
** Necessite 4 parametres minimum (le 2e et 3e sont ignores par notre serveur).
** PASS doit avoir ete envoye avant.
** Ne peut pas etre utilise apres enregistrement (pas de re-registration).
*/
void Server::_cmdUser(Client* c, std::vector<std::string>& args) {
	if (c->isRegistered())
		return _sendReply(c, ":ircserv 462 " + c->getNick() + " :You may not reregister\r\n");
	if (args.size() < 4)
		return _sendReply(c, ":ircserv 461 * USER :Not enough parameters\r\n");
	if (!c->hasPasswd())
		return _sendReply(c, ":ircserv 451 * :You have not registered (PASS required)\r\n");

	c->setUser(args[0]);
	c->setRealname(args[3]);

	if (c->isRegistered())
		_welcomeClient(c);
}

/* ========================================================================== */
/*   JOIN - Rejoindre un ou plusieurs channels                                */
/* ========================================================================== */

/*
** JOIN <channel>{,<channel>} [<key>{,<key>}]
** Permet de rejoindre un ou plusieurs channels (separes par des virgules).
** Des cles peuvent etre fournies pour les channels proteges par mot de passe.
**
** Verifications pour chaque channel :
** - Le nom doit commencer par #
** - Si mode +i (invite-only) : le client doit avoir ete invite
** - Si mode +k (cle) : la cle fournie doit correspondre
** - Si mode +l (limite) : le nombre de membres ne doit pas depasser la limite
**
** Le premier client a rejoindre un channel en devient automatiquement operateur.
** Apres le join, on envoie : le broadcast JOIN, le topic (si defini), la liste NAMES.
*/
void Server::_cmdJoin(Client* c, std::vector<std::string>& args) {
	if (args.empty())
		return _sendReply(c, ":ircserv 461 " + c->getNick() + " JOIN :Not enough parameters\r\n");

	std::vector<std::string> chans = _split(args[0], ',');
	std::vector<std::string> keys;
	if (args.size() > 1)
		keys = _split(args[1], ',');

	for (size_t i = 0; i < chans.size(); i++) {
		std::string name = chans[i];
		if (name.empty() || name[0] != '#') {
			_sendReply(c, ":ircserv 403 " + c->getNick() + " " + name + " :No such channel\r\n");
			continue;
		}

		bool isNew = (_channels.find(name) == _channels.end());
		Channel* ch = _getOrCreateChannel(name);

		// Si deja membre, on ignore silencieusement
		if (ch->isMember(c)) continue;

		// Verification mode invite-only (+i)
		if (ch->isInviteOnly() && !ch->isInvited(c)) {
			_sendReply(c, ":ircserv 473 " + c->getNick() + " " + name + " :Cannot join channel (+i)\r\n");
			continue;
		}
		// Verification cle (+k)
		if (ch->hasKey()) {
			std::string key = (i < keys.size()) ? keys[i] : "";
			if (key != ch->getKey()) {
				_sendReply(c, ":ircserv 475 " + c->getNick() + " " + name + " :Cannot join channel (+k)\r\n");
				continue;
			}
		}
		// Verification limite de membres (+l)
		if (ch->hasLimit() && ch->memberCount() >= ch->getLimit()) {
			_sendReply(c, ":ircserv 471 " + c->getNick() + " " + name + " :Cannot join channel (+l)\r\n");
			continue;
		}

		// Ajout du client au channel
		ch->addMember(c);
		if (isNew)
			ch->addOperator(c);  // Premier membre = operateur
		ch->removeInvited(c);    // Retire de la liste d'invites (invitation consommee)

		// Broadcast du JOIN a tous les membres (y compris le nouveau)
		ch->broadcast(":" + c->getPrefix() + " JOIN " + name + "\r\n", NULL);

		// Envoie le topic s'il est defini
		if (!ch->getTopic().empty())
			_sendReply(c, ":ircserv 332 " + c->getNick() + " " + name + " :" + ch->getTopic() + "\r\n");

		// Envoie la liste des membres (NAMES) - les ops sont prefixes par @
		std::string names;
		std::vector<Client*> members = ch->getMembers();
		for (size_t j = 0; j < members.size(); j++) {
			if (j > 0) names += " ";
			if (ch->isOperator(members[j])) names += "@";
			names += members[j]->getNick();
		}
		_sendReply(c, ":ircserv 353 " + c->getNick() + " = " + name + " :" + names + "\r\n");
		_sendReply(c, ":ircserv 366 " + c->getNick() + " " + name + " :End of /NAMES list\r\n");
	}
}

/* ========================================================================== */
/*   PART - Quitter un ou plusieurs channels                                  */
/* ========================================================================== */

/*
** PART <channel>{,<channel>} [:<message>]
** Quitte un ou plusieurs channels avec un message optionnel.
** Broadcast le PART a tous les membres avant de retirer le client.
** Si le channel devient vide, il est supprime.
*/
void Server::_cmdPart(Client* c, std::vector<std::string>& args) {
	if (args.empty())
		return _sendReply(c, ":ircserv 461 " + c->getNick() + " PART :Not enough parameters\r\n");

	std::vector<std::string> chans = _split(args[0], ',');
	std::string reason = args.size() > 1 ? args[1] : "";

	for (size_t i = 0; i < chans.size(); i++) {
		std::map<std::string, Channel*>::iterator it = _channels.find(chans[i]);
		if (it == _channels.end()) {
			_sendReply(c, ":ircserv 403 " + c->getNick() + " " + chans[i] + " :No such channel\r\n");
			continue;
		}
		if (!it->second->isMember(c)) {
			_sendReply(c, ":ircserv 442 " + c->getNick() + " " + chans[i] + " :You're not on that channel\r\n");
			continue;
		}
		std::string msg = ":" + c->getPrefix() + " PART " + chans[i];
		if (!reason.empty()) msg += " :" + reason;
		msg += "\r\n";
		it->second->broadcast(msg, NULL);
		it->second->removeMember(c);
		// Supprime le channel s'il est vide
		if (it->second->memberCount() == 0) {
			delete it->second;
			_channels.erase(it);
		}
	}
}

/* ========================================================================== */
/*   PRIVMSG - Message prive (a un user ou un channel)                        */
/* ========================================================================== */

/*
** PRIVMSG <target> :<message>
** Envoie un message a un utilisateur ou a un channel.
** - Si target commence par # : message envoye a tous les membres du channel (sauf l'emetteur)
** - Sinon : message envoye directement au client cible
** L'emetteur doit etre membre du channel pour y envoyer un message.
*/
void Server::_cmdPrivmsg(Client* c, std::vector<std::string>& args) {
	if (args.empty())
		return _sendReply(c, ":ircserv 411 " + c->getNick() + " :No recipient given (PRIVMSG)\r\n");
	if (args.size() < 2)
		return _sendReply(c, ":ircserv 412 " + c->getNick() + " :No text to send\r\n");

	std::string target = args[0];
	std::string msg = ":" + c->getPrefix() + " PRIVMSG " + target + " :" + args[1] + "\r\n";

	if (target[0] == '#') {
		// Message vers un channel
		std::map<std::string, Channel*>::iterator it = _channels.find(target);
		if (it == _channels.end())
			return _sendReply(c, ":ircserv 403 " + c->getNick() + " " + target + " :No such channel\r\n");
		if (!it->second->isMember(c))
			return _sendReply(c, ":ircserv 404 " + c->getNick() + " " + target + " :Cannot send to channel\r\n");
		it->second->broadcast(msg, c);  // Envoie a tous sauf l'emetteur
	} else {
		// Message prive vers un utilisateur
		Client* dest = _findClientByNick(target);
		if (!dest)
			return _sendReply(c, ":ircserv 401 " + c->getNick() + " " + target + " :No such nick/channel\r\n");
		_sendReply(dest, msg);
	}
}

/* ========================================================================== */
/*   KICK - Expulser un utilisateur d'un channel (operateur requis)           */
/* ========================================================================== */

/*
** KICK <channel> <user> [:<reason>]
** Expulse un utilisateur d'un channel. Seul un operateur peut kick.
** Le message de kick est broadcast a tout le channel avant la suppression.
** Si le channel devient vide apres le kick, il est supprime.
*/
void Server::_cmdKick(Client* c, std::vector<std::string>& args) {
	if (args.size() < 2)
		return _sendReply(c, ":ircserv 461 " + c->getNick() + " KICK :Not enough parameters\r\n");

	std::map<std::string, Channel*>::iterator it = _channels.find(args[0]);
	if (it == _channels.end())
		return _sendReply(c, ":ircserv 403 " + c->getNick() + " " + args[0] + " :No such channel\r\n");
	Channel* ch = it->second;
	if (!ch->isMember(c))
		return _sendReply(c, ":ircserv 442 " + c->getNick() + " " + args[0] + " :You're not on that channel\r\n");
	if (!ch->isOperator(c))
		return _sendReply(c, ":ircserv 482 " + c->getNick() + " " + args[0] + " :You're not channel operator\r\n");

	Client* target = _findClientByNick(args[1]);
	if (!target || !ch->isMember(target))
		return _sendReply(c, ":ircserv 441 " + c->getNick() + " " + args[1] + " " + args[0] + " :They aren't on that channel\r\n");

	std::string reason = args.size() > 2 ? args[2] : c->getNick();
	ch->broadcast(":" + c->getPrefix() + " KICK " + args[0] + " " + target->getNick() + " :" + reason + "\r\n", NULL);
	ch->removeMember(target);
	if (ch->memberCount() == 0) {
		delete ch;
		_channels.erase(it);
	}
}

/* ========================================================================== */
/*   INVITE - Inviter un utilisateur dans un channel (operateur requis)       */
/* ========================================================================== */

/*
** INVITE <nick> <channel>
** Invite un utilisateur a rejoindre un channel. Seul un operateur peut inviter.
** L'invitation est necessaire pour rejoindre un channel en mode +i (invite-only).
** L'invitation est consommee quand le client rejoint le channel (removeInvited dans JOIN).
*/
void Server::_cmdInvite(Client* c, std::vector<std::string>& args) {
	if (args.size() < 2)
		return _sendReply(c, ":ircserv 461 " + c->getNick() + " INVITE :Not enough parameters\r\n");

	Client* target = _findClientByNick(args[0]);
	if (!target)
		return _sendReply(c, ":ircserv 401 " + c->getNick() + " " + args[0] + " :No such nick/channel\r\n");

	std::map<std::string, Channel*>::iterator it = _channels.find(args[1]);
	if (it == _channels.end())
		return _sendReply(c, ":ircserv 403 " + c->getNick() + " " + args[1] + " :No such channel\r\n");
	Channel* ch = it->second;
	if (!ch->isMember(c))
		return _sendReply(c, ":ircserv 442 " + c->getNick() + " " + args[1] + " :You're not on that channel\r\n");
	if (!ch->isOperator(c))
		return _sendReply(c, ":ircserv 482 " + c->getNick() + " " + args[1] + " :You're not channel operator\r\n");
	if (ch->isMember(target))
		return _sendReply(c, ":ircserv 443 " + c->getNick() + " " + args[0] + " " + args[1] + " :is already on channel\r\n");

	ch->addInvited(target);
	// Confirmation a l'operateur (RPL_INVITING)
	_sendReply(c, ":ircserv 341 " + c->getNick() + " " + args[0] + " " + args[1] + "\r\n");
	// Notification a l'invite
	_sendReply(target, ":" + c->getPrefix() + " INVITE " + target->getNick() + " " + args[1] + "\r\n");
}

/* ========================================================================== */
/*   TOPIC - Voir/modifier le topic d'un channel                             */
/* ========================================================================== */

/*
** TOPIC <channel> [:<topic>]
** Sans argument topic : affiche le topic actuel (331 si vide, 332 si defini)
** Avec argument topic : change le topic et broadcast le changement
** Si mode +t est actif, seuls les operateurs peuvent changer le topic.
*/
void Server::_cmdTopic(Client* c, std::vector<std::string>& args) {
	if (args.empty())
		return _sendReply(c, ":ircserv 461 " + c->getNick() + " TOPIC :Not enough parameters\r\n");

	std::map<std::string, Channel*>::iterator it = _channels.find(args[0]);
	if (it == _channels.end())
		return _sendReply(c, ":ircserv 403 " + c->getNick() + " " + args[0] + " :No such channel\r\n");
	Channel* ch = it->second;
	if (!ch->isMember(c))
		return _sendReply(c, ":ircserv 442 " + c->getNick() + " " + args[0] + " :You're not on that channel\r\n");

	// Mode consultation : affiche le topic actuel
	if (args.size() == 1) {
		if (ch->getTopic().empty())
			_sendReply(c, ":ircserv 331 " + c->getNick() + " " + args[0] + " :No topic is set\r\n");
		else
			_sendReply(c, ":ircserv 332 " + c->getNick() + " " + args[0] + " :" + ch->getTopic() + "\r\n");
		return;
	}

	// Mode modification : verifie les permissions si +t
	if (ch->isTopicRestricted() && !ch->isOperator(c))
		return _sendReply(c, ":ircserv 482 " + c->getNick() + " " + args[0] + " :You're not channel operator\r\n");

	ch->setTopic(args[1]);
	ch->broadcast(":" + c->getPrefix() + " TOPIC " + args[0] + " :" + args[1] + "\r\n", NULL);
}

/* ========================================================================== */
/*   MODE - Modifier les modes d'un channel (operateur requis)                */
/* ========================================================================== */

/*
** MODE <channel> [<modestring> [<mode arguments>...]]
** Sans modestring : affiche les modes actuels du channel (RPL_CHANNELMODEIS 324)
** Avec modestring : modifie les modes (operateur requis)
**
** Modes supportes :
** +i / -i : invite-only (seuls les invites peuvent JOIN)
** +t / -t : topic restreint (seuls les ops peuvent changer le topic)
** +k <key> / -k : definir/retirer un mot de passe pour le channel
** +o <nick> / -o <nick> : donner/retirer le statut operateur a un membre
** +l <limit> / -l : definir/retirer une limite de membres
**
** Le parsing du modestring est complexe :
** - '+' et '-' changent le sens (ajout/retrait)
** - Certains modes necessitent un parametre supplementaire (+k, +o, +l, -o)
** - On accumule les modes appliques pour les broadcaster en une seule fois
*/
void Server::_cmdMode(Client* c, std::vector<std::string>& args) {
	if (args.empty())
		return _sendReply(c, ":ircserv 461 " + c->getNick() + " MODE :Not enough parameters\r\n");

	std::string target = args[0];

	// Mode utilisateur : on repond simplement "+" (pas de modes user supportes)
	if (target[0] != '#') {
		if (target != c->getNick())
			return _sendReply(c, ":ircserv 502 " + c->getNick() + " :Can't change mode for other users\r\n");
		_sendReply(c, ":ircserv 221 " + c->getNick() + " +\r\n");
		return;
	}

	std::map<std::string, Channel*>::iterator it = _channels.find(target);
	if (it == _channels.end())
		return _sendReply(c, ":ircserv 403 " + c->getNick() + " " + target + " :No such channel\r\n");
	Channel* ch = it->second;

	// Sans modestring : affiche les modes actuels
	if (args.size() == 1) {
		std::string modes = ch->getModeString();
		_sendReply(c, ":ircserv 324 " + c->getNick() + " " + target + " " + (modes.empty() ? "+" : modes) + "\r\n");
		return;
	}

	// Modification des modes : operateur requis
	if (!ch->isOperator(c))
		return _sendReply(c, ":ircserv 482 " + c->getNick() + " " + target + " :You're not channel operator\r\n");

	std::string modeStr = args[1];
	size_t paramIdx = 2;       // Index du prochain parametre de mode a consommer
	bool adding = true;        // true = on ajoute le mode, false = on le retire
	std::string appliedModes;  // Modes effectivement appliques (pour le broadcast)
	std::string appliedParams; // Parametres des modes appliques

	for (size_t i = 0; i < modeStr.length(); i++) {
		char m = modeStr[i];
		if (m == '+') { adding = true; continue; }
		if (m == '-') { adding = false; continue; }

		switch (m) {
			case 'i':
				// Mode invite-only : pas de parametre
				ch->setInviteOnly(adding);
				appliedModes += (adding ? "+i" : "-i");
				break;
			case 't':
				// Mode topic restreint : pas de parametre
				ch->setTopicRestricted(adding);
				appliedModes += (adding ? "+t" : "-t");
				break;
			case 'k':
				// Mode cle : necessite un parametre pour +k, pas pour -k
				if (adding) {
					if (paramIdx >= args.size()) {
						_sendReply(c, ":ircserv 461 " + c->getNick() + " MODE :Not enough parameters\r\n");
						continue;
					}
					ch->setKey(args[paramIdx]);
					appliedModes += "+k";
					appliedParams += " " + args[paramIdx];
					paramIdx++;
				} else {
					ch->removeKey();
					appliedModes += "-k";
				}
				break;
			case 'o': {
				// Mode operateur : necessite toujours un parametre (le nick)
				if (paramIdx >= args.size()) {
					_sendReply(c, ":ircserv 461 " + c->getNick() + " MODE :Not enough parameters\r\n");
					continue;
				}
				Client* t = _findClientByNick(args[paramIdx]);
				if (!t || !ch->isMember(t)) {
					_sendReply(c, ":ircserv 441 " + c->getNick() + " " + args[paramIdx] + " " + target + " :They aren't on that channel\r\n");
					paramIdx++;
					continue;
				}
				if (adding)
					ch->addOperator(t);
				else
					ch->removeOperator(t);
				appliedModes += std::string(adding ? "+" : "-") + "o";
				appliedParams += " " + args[paramIdx];
				paramIdx++;
				break;
			}
			case 'l':
				// Mode limite : necessite un parametre pour +l, pas pour -l
				if (adding) {
					if (paramIdx >= args.size()) {
						_sendReply(c, ":ircserv 461 " + c->getNick() + " MODE :Not enough parameters\r\n");
						continue;
					}
					int limit = std::atoi(args[paramIdx].c_str());
					if (limit <= 0) { paramIdx++; continue; }  // Ignore les limites invalides
					ch->setLimit(limit);
					appliedModes += "+l";
					appliedParams += " " + args[paramIdx];
					paramIdx++;
				} else {
					ch->removeLimit();
					appliedModes += "-l";
				}
				break;
			default:
				// Mode inconnu
				_sendReply(c, ":ircserv 472 " + c->getNick() + " " + std::string(1, m) + " :is unknown mode char to me\r\n");
				break;
		}
	}

	// Broadcast les modes appliques a tout le channel
	if (!appliedModes.empty())
		ch->broadcast(":" + c->getPrefix() + " MODE " + target + " " + appliedModes + appliedParams + "\r\n", NULL);
}

/* ========================================================================== */
/*   QUIT - Deconnexion propre du client                                      */
/* ========================================================================== */

/*
** QUIT [:<message>]
** Le client se deconnecte proprement.
** On broadcast le QUIT a tous les channels ou il est present,
** puis on lui envoie "ERROR :Closing link" et on le marque pour suppression.
** La suppression effective se fait dans _flushRemovals() en fin de boucle.
*/
void Server::_cmdQuit(Client* c, std::vector<std::string>& args) {
	std::string reason = args.empty() ? "Leaving" : args[0];
	std::string msg = ":" + c->getPrefix() + " QUIT :" + reason + "\r\n";

	// Notifie tous les channels ou le client est present
	for (std::map<std::string, Channel*>::iterator it = _channels.begin(); it != _channels.end(); ++it)
		if (it->second->isMember(c))
			it->second->broadcast(msg, c);

	c->queueMessage("ERROR :Closing link\r\n");
	_toRemove.insert(c->getFd());
}

/* ========================================================================== */
/*   PING - Keepalive                                                         */
/* ========================================================================== */

/*
** PING <token>
** Le client envoie PING pour verifier que la connexion est active.
** Le serveur repond PONG avec le meme token.
*/
void Server::_cmdPing(Client* c, std::vector<std::string>& args) {
	if (args.empty())
		return _sendReply(c, ":ircserv 409 " + c->getNick() + " :No origin specified\r\n");
	_sendReply(c, ":ircserv PONG ircserv :" + args[0] + "\r\n");
}
