#include "Server.hpp"
#include <sstream>
#include <cstdlib>
#include <sys/socket.h>

// PASS <password>
void Server::_cmdPass(Client* c, std::vector<std::string>& args) {
	if (c->isRegistered())
		return _sendReply(c, ":ircserv 462 " + c->getNick() + " :You may not reregister\r\n");
	if (args.empty())
		return _sendReply(c, ":ircserv 461 * PASS :Not enough parameters\r\n");
	if (args[0] != _password)
		return _sendReply(c, ":ircserv 464 * :Password incorrect\r\n");
	c->setPasswd(true);
}

// NICK <nickname>
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

	if (!oldPrefix.empty())
		_sendReply(c, ":" + oldPrefix + " NICK " + nick + "\r\n");
	if (!wasRegistered && c->isRegistered())
		_welcomeClient(c);
}

// USER <username> <mode> <unused> :<realname>
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

// JOIN <channel>{,<channel>} [<key>{,<key>}]
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

		if (ch->isMember(c)) continue;
		if (ch->isInviteOnly() && !ch->isInvited(c)) {
			_sendReply(c, ":ircserv 473 " + c->getNick() + " " + name + " :Cannot join channel (+i)\r\n");
			continue;
		}
		if (ch->hasKey()) {
			std::string key = (i < keys.size()) ? keys[i] : "";
			if (key != ch->getKey()) {
				_sendReply(c, ":ircserv 475 " + c->getNick() + " " + name + " :Cannot join channel (+k)\r\n");
				continue;
			}
		}
		if (ch->hasLimit() && ch->memberCount() >= ch->getLimit()) {
			_sendReply(c, ":ircserv 471 " + c->getNick() + " " + name + " :Cannot join channel (+l)\r\n");
			continue;
		}

		ch->addMember(c);
		if (isNew)
			ch->addOperator(c);
		ch->removeInvited(c);

		ch->broadcast(":" + c->getPrefix() + " JOIN " + name + "\r\n", NULL);

		if (!ch->getTopic().empty())
			_sendReply(c, ":ircserv 332 " + c->getNick() + " " + name + " :" + ch->getTopic() + "\r\n");

		// NAMES list
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

// PART <channel>{,<channel>} [:<message>]
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
		if (it->second->memberCount() == 0) {
			delete it->second;
			_channels.erase(it);
		}
	}
}

// PRIVMSG <target> :<message>
void Server::_cmdPrivmsg(Client* c, std::vector<std::string>& args) {
	if (args.empty())
		return _sendReply(c, ":ircserv 411 " + c->getNick() + " :No recipient given (PRIVMSG)\r\n");
	if (args.size() < 2)
		return _sendReply(c, ":ircserv 412 " + c->getNick() + " :No text to send\r\n");

	std::string target = args[0];
	std::string msg = ":" + c->getPrefix() + " PRIVMSG " + target + " :" + args[1] + "\r\n";

	if (target[0] == '#') {
		std::map<std::string, Channel*>::iterator it = _channels.find(target);
		if (it == _channels.end())
			return _sendReply(c, ":ircserv 403 " + c->getNick() + " " + target + " :No such channel\r\n");
		if (!it->second->isMember(c))
			return _sendReply(c, ":ircserv 404 " + c->getNick() + " " + target + " :Cannot send to channel\r\n");
		it->second->broadcast(msg, c);
	} else {
		Client* dest = _findClientByNick(target);
		if (!dest)
			return _sendReply(c, ":ircserv 401 " + c->getNick() + " " + target + " :No such nick/channel\r\n");
		_sendReply(dest, msg);
	}
}

// KICK <channel> <user> [:<reason>]
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

// INVITE <nick> <channel>
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
	_sendReply(c, ":ircserv 341 " + c->getNick() + " " + args[0] + " " + args[1] + "\r\n");
	_sendReply(target, ":" + c->getPrefix() + " INVITE " + target->getNick() + " " + args[1] + "\r\n");
}

// TOPIC <channel> [:<topic>]
void Server::_cmdTopic(Client* c, std::vector<std::string>& args) {
	if (args.empty())
		return _sendReply(c, ":ircserv 461 " + c->getNick() + " TOPIC :Not enough parameters\r\n");

	std::map<std::string, Channel*>::iterator it = _channels.find(args[0]);
	if (it == _channels.end())
		return _sendReply(c, ":ircserv 403 " + c->getNick() + " " + args[0] + " :No such channel\r\n");
	Channel* ch = it->second;
	if (!ch->isMember(c))
		return _sendReply(c, ":ircserv 442 " + c->getNick() + " " + args[0] + " :You're not on that channel\r\n");

	if (args.size() == 1) {
		if (ch->getTopic().empty())
			_sendReply(c, ":ircserv 331 " + c->getNick() + " " + args[0] + " :No topic is set\r\n");
		else
			_sendReply(c, ":ircserv 332 " + c->getNick() + " " + args[0] + " :" + ch->getTopic() + "\r\n");
		return;
	}

	if (ch->isTopicRestricted() && !ch->isOperator(c))
		return _sendReply(c, ":ircserv 482 " + c->getNick() + " " + args[0] + " :You're not channel operator\r\n");

	ch->setTopic(args[1]);
	ch->broadcast(":" + c->getPrefix() + " TOPIC " + args[0] + " :" + args[1] + "\r\n", NULL);
}

// MODE <channel> [<modestring> [<mode arguments>...]]
void Server::_cmdMode(Client* c, std::vector<std::string>& args) {
	if (args.empty())
		return _sendReply(c, ":ircserv 461 " + c->getNick() + " MODE :Not enough parameters\r\n");

	std::string target = args[0];

	// User mode - just ignore / reply empty
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

	if (args.size() == 1) {
		std::string modes = ch->getModeString();
		_sendReply(c, ":ircserv 324 " + c->getNick() + " " + target + " " + (modes.empty() ? "+" : modes) + "\r\n");
		return;
	}

	if (!ch->isOperator(c))
		return _sendReply(c, ":ircserv 482 " + c->getNick() + " " + target + " :You're not channel operator\r\n");

	std::string modeStr = args[1];
	size_t paramIdx = 2;
	bool adding = true;
	std::string appliedModes;
	std::string appliedParams;

	for (size_t i = 0; i < modeStr.length(); i++) {
		char m = modeStr[i];
		if (m == '+') { adding = true; continue; }
		if (m == '-') { adding = false; continue; }

		switch (m) {
			case 'i':
				ch->setInviteOnly(adding);
				appliedModes += (adding ? "+i" : "-i");
				break;
			case 't':
				ch->setTopicRestricted(adding);
				appliedModes += (adding ? "+t" : "-t");
				break;
			case 'k':
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
				if (adding) {
					if (paramIdx >= args.size()) {
						_sendReply(c, ":ircserv 461 " + c->getNick() + " MODE :Not enough parameters\r\n");
						continue;
					}
					int limit = std::atoi(args[paramIdx].c_str());
					if (limit <= 0) { paramIdx++; continue; }
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
				_sendReply(c, ":ircserv 472 " + c->getNick() + " " + std::string(1, m) + " :is unknown mode char to me\r\n");
				break;
		}
	}

	if (!appliedModes.empty())
		ch->broadcast(":" + c->getPrefix() + " MODE " + target + " " + appliedModes + appliedParams + "\r\n", NULL);
}

// QUIT [:<message>]
void Server::_cmdQuit(Client* c, std::vector<std::string>& args) {
	std::string reason = args.empty() ? "Leaving" : args[0];
	std::string msg = ":" + c->getPrefix() + " QUIT :" + reason + "\r\n";

	for (std::map<std::string, Channel*>::iterator it = _channels.begin(); it != _channels.end(); ++it)
		if (it->second->isMember(c))
			it->second->broadcast(msg, c);

	send(c->getFd(), "ERROR :Closing link\r\n", 21, 0);
	_toRemove.insert(c->getFd());
}

// PING <token>
void Server::_cmdPing(Client* c, std::vector<std::string>& args) {
	if (args.empty())
		return _sendReply(c, ":ircserv 409 " + c->getNick() + " :No origin specified\r\n");
	_sendReply(c, ":ircserv PONG ircserv :" + args[0] + "\r\n");
}
