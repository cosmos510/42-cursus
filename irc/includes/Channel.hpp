#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <string>
#include <vector>
#include <set>

class Client;

class Channel {
public:
	Channel(const std::string& name);
	~Channel();

	const std::string& getName() const;
	const std::string& getTopic() const;
	const std::string& getKey() const;
	int getLimit() const;
	bool isInviteOnly() const;
	bool isTopicRestricted() const;
	bool hasKey() const;
	bool hasLimit() const;
	std::string getModeString() const;

	void setTopic(const std::string& topic);
	void setKey(const std::string& key);
	void removeKey();
	void setLimit(int limit);
	void removeLimit();
	void setInviteOnly(bool val);
	void setTopicRestricted(bool val);

	bool isMember(Client* c) const;
	bool isOperator(Client* c) const;
	bool isInvited(Client* c) const;
	void addMember(Client* c);
	void removeMember(Client* c);
	void addOperator(Client* c);
	void removeOperator(Client* c);
	void addInvited(Client* c);
	void removeInvited(Client* c);
	int memberCount() const;
	std::vector<Client*> getMembers() const;

	void broadcast(const std::string& msg, Client* exclude);

private:
	std::string _name;
	std::string _topic;
	std::string _key;
	int _limit;
	bool _inviteOnly;
	bool _topicRestricted;
	std::vector<Client*> _members;
	std::set<Client*> _operators;
	std::set<Client*> _invited;
};

#endif
