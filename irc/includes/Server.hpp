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
	Server(int port, const std::string& password);
	~Server();

	void run();

private:
	int _port;
	std::string _password;
	int _listenFd;
	std::vector<struct pollfd> _pollfds;
	std::map<int, Client*> _clients;
	std::map<std::string, Channel*> _channels;
	std::set<int> _toRemove;

	void _initSocket();
	void _acceptClient();
	void _receiveData(int fd);
	void _processLine(Client* client, const std::string& line);
	void _removeClient(int fd);
	void _flushRemovals();
	void _sendReply(Client* client, const std::string& msg);
	void _sendReply(int fd, const std::string& msg);

	Client* _findClientByNick(const std::string& nick);
	Channel* _getOrCreateChannel(const std::string& name);

	void _cmdPass(Client* c, std::vector<std::string>& args);
	void _cmdNick(Client* c, std::vector<std::string>& args);
	void _cmdUser(Client* c, std::vector<std::string>& args);
	void _cmdJoin(Client* c, std::vector<std::string>& args);
	void _cmdPart(Client* c, std::vector<std::string>& args);
	void _cmdPrivmsg(Client* c, std::vector<std::string>& args);
	void _cmdKick(Client* c, std::vector<std::string>& args);
	void _cmdInvite(Client* c, std::vector<std::string>& args);
	void _cmdTopic(Client* c, std::vector<std::string>& args);
	void _cmdMode(Client* c, std::vector<std::string>& args);
	void _cmdQuit(Client* c, std::vector<std::string>& args);
	void _cmdPing(Client* c, std::vector<std::string>& args);

	void _welcomeClient(Client* c);

	static std::vector<std::string> _split(const std::string& s, char delim);
	static std::string _toUpper(const std::string& s);
};

#endif
