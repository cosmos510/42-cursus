#include "Channel.hpp"
#include "Client.hpp"
#include <sys/socket.h>
#include <algorithm>

Channel::Channel(const std::string& name)
	: _name(name), _limit(0), _inviteOnly(false), _topicRestricted(false) {}

Channel::~Channel() {}

const std::string& Channel::getName() const { return _name; }
const std::string& Channel::getTopic() const { return _topic; }
const std::string& Channel::getKey() const { return _key; }
int Channel::getLimit() const { return _limit; }
bool Channel::isInviteOnly() const { return _inviteOnly; }
bool Channel::isTopicRestricted() const { return _topicRestricted; }
bool Channel::hasKey() const { return !_key.empty(); }
bool Channel::hasLimit() const { return _limit > 0; }

std::string Channel::getModeString() const {
	std::string modes = "+";
	if (_inviteOnly) modes += "i";
	if (_topicRestricted) modes += "t";
	if (hasKey()) modes += "k";
	if (hasLimit()) modes += "l";
	return modes.length() > 1 ? modes : "";
}

void Channel::setTopic(const std::string& topic) { _topic = topic; }
void Channel::setKey(const std::string& key) { _key = key; }
void Channel::removeKey() { _key.clear(); }
void Channel::setLimit(int limit) { _limit = limit; }
void Channel::removeLimit() { _limit = 0; }
void Channel::setInviteOnly(bool val) { _inviteOnly = val; }
void Channel::setTopicRestricted(bool val) { _topicRestricted = val; }

bool Channel::isMember(Client* c) const {
	return std::find(_members.begin(), _members.end(), c) != _members.end();
}

bool Channel::isOperator(Client* c) const { return _operators.count(c); }
bool Channel::isInvited(Client* c) const { return _invited.count(c); }

void Channel::addMember(Client* c) {
	if (!isMember(c))
		_members.push_back(c);
}

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

void Channel::broadcast(const std::string& msg, Client* exclude) {
	for (size_t i = 0; i < _members.size(); i++) {
		if (_members[i] != exclude)
			send(_members[i]->getFd(), msg.c_str(), msg.length(), 0);
	}
}
