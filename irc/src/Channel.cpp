/* ************************************************************************** */
/*                                                                            */
/*   Channel.cpp - Implementation de la classe Channel                        */
/*                                                                            */
/*   Gere les membres, operateurs, invites et modes d'un channel IRC.         */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Client.hpp"
#include <algorithm>

/* Constructeur : initialise un channel sans mode actif et sans limite */
Channel::Channel(const std::string& name)
	: _name(name), _limit(0), _inviteOnly(false), _topicRestricted(false) {}

Channel::~Channel() {}

/* --- Getters --- */
const std::string& Channel::getName() const { return _name; }
const std::string& Channel::getTopic() const { return _topic; }
const std::string& Channel::getKey() const { return _key; }
int Channel::getLimit() const { return _limit; }
bool Channel::isInviteOnly() const { return _inviteOnly; }
bool Channel::isTopicRestricted() const { return _topicRestricted; }
bool Channel::hasKey() const { return !_key.empty(); }
bool Channel::hasLimit() const { return _limit > 0; }

/*
** Construit la string des modes actifs pour la reponse RPL_CHANNELMODEIS (324).
** Exemple : si invite-only et topic restreint sont actifs -> "+it"
** Retourne "" si aucun mode n'est actif.
*/
std::string Channel::getModeString() const {
	std::string modes = "+";
	if (_inviteOnly) modes += "i";
	if (_topicRestricted) modes += "t";
	if (hasKey()) modes += "k";
	if (hasLimit()) modes += "l";
	return modes.length() > 1 ? modes : "";
}

/* --- Setters pour les modes --- */
void Channel::setTopic(const std::string& topic) { _topic = topic; }
void Channel::setKey(const std::string& key) { _key = key; }
void Channel::removeKey() { _key.clear(); }
void Channel::setLimit(int limit) { _limit = limit; }
void Channel::removeLimit() { _limit = 0; }
void Channel::setInviteOnly(bool val) { _inviteOnly = val; }
void Channel::setTopicRestricted(bool val) { _topicRestricted = val; }

/* ========================================================================== */
/*   Gestion des membres                                                      */
/* ========================================================================== */

/* Verifie si un client est membre du channel */
bool Channel::isMember(Client* c) const {
	return std::find(_members.begin(), _members.end(), c) != _members.end();
}

/* Verifie si un client est operateur du channel */
bool Channel::isOperator(Client* c) const { return _operators.count(c); }

/* Verifie si un client a ete invite (pour le mode +i) */
bool Channel::isInvited(Client* c) const { return _invited.count(c); }

/* Ajoute un client comme membre (verifie qu'il n'est pas deja present) */
void Channel::addMember(Client* c) {
	if (!isMember(c))
		_members.push_back(c);
}

/*
** Retire un membre du channel.
** Le retire aussi des operateurs et des invites pour eviter les references pendantes.
** Utilise l'idiome erase-remove pour supprimer efficacement d'un vector.
*/
void Channel::removeMember(Client* c) {
	_members.erase(std::remove(_members.begin(), _members.end(), c), _members.end());
	_operators.erase(c);
	_invited.erase(c);
}

void Channel::addOperator(Client* c) { _operators.insert(c); }
void Channel::removeOperator(Client* c) { _operators.erase(c); }
void Channel::addInvited(Client* c) { _invited.insert(c); }
void Channel::removeInvited(Client* c) { _invited.erase(c); }
int Channel::memberCount() const { return _members.size(); }
std::vector<Client*> Channel::getMembers() const { return _members; }

/* ========================================================================== */
/*   Broadcast                                                                */
/* ========================================================================== */

/*
** Envoie un message a tous les membres du channel sauf 'exclude'.
**
** Utilise queueMessage() au lieu de send() direct :
** - Les messages sont stockes dans le buffer d'envoi de chaque client
** - Ils seront envoyes au prochain cycle poll() quand POLLOUT est signale
** - Cela evite de bloquer si un client a son buffer TCP plein (ex: client stoppe)
**
** exclude = NULL : envoie a tout le monde (JOIN, KICK, TOPIC, MODE)
** exclude = emetteur : n'envoie pas a l'emetteur (PRIVMSG, QUIT)
*/
void Channel::broadcast(const std::string& msg, Client* exclude) {
	for (size_t i = 0; i < _members.size(); i++) {
		if (_members[i] != exclude)
			_members[i]->queueMessage(msg);
	}
}
