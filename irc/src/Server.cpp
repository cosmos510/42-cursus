#include "Server.hpp"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sstream>
#include <csignal>

static const size_t MAX_BUFFER = 4096;

Server::Server(int port, const std::string& password) : _port(port), _password(password), _listenFd(-1) {}

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

void Server::_initSocket() {
	_listenFd = socket(AF_INET, SOCK_STREAM, 0);
	if (_listenFd < 0)
		throw std::runtime_error("socket() failed");

	int opt = 1;
	if (setsockopt(_listenFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
		close(_listenFd);
		_listenFd = -1;
		throw std::runtime_error("setsockopt() failed");
	}
	if (fcntl(_listenFd, F_SETFL, O_NONBLOCK) < 0) {
		close(_listenFd);
		_listenFd = -1;
		throw std::runtime_error("fcntl() failed");
	}

	struct sockaddr_in addr;
	std::memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(_port);

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

	struct pollfd pfd;
	pfd.fd = _listenFd;
	pfd.events = POLLIN;
	pfd.revents = 0;
	_pollfds.push_back(pfd);
	std::cout << "Server listening on port " << _port << std::endl;
}

static volatile bool g_running = true;

static void signalHandler(int) { g_running = false; }

void Server::run() {
	_initSocket();

	struct sigaction sa;
	sa.sa_handler = signalHandler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	::sigaction(SIGINT, &sa, NULL);
	::sigaction(SIGTERM, &sa, NULL);

	while (g_running) {
		int ret = poll(&_pollfds[0], _pollfds.size(), -1);
		if (ret < 0) {
			if (!g_running) break;
			continue;
		}

		// Collect fds to process (avoid issues with vector modification during iteration)
		std::vector<struct pollfd> snapshot(_pollfds);
		for (size_t i = 0; i < snapshot.size(); i++) {
			int fd = snapshot[i].fd;
			short rev = snapshot[i].revents;
			if (!rev) continue;

			if (fd == _listenFd) {
				if (rev & POLLIN)
					_acceptClient();
				continue;
			}
			// Client fd
			if (rev & (POLLERR | POLLHUP | POLLNVAL)) {
				_toRemove.insert(fd);
				continue;
			}
			if (rev & POLLIN) {
				if (_clients.find(fd) != _clients.end())
					_receiveData(fd);
			}
		}
		_flushRemovals();
	}
	std::cout << "\nServer shutting down." << std::endl;
}

void Server::_acceptClient() {
	struct sockaddr_in addr;
	socklen_t len = sizeof(addr);
	int fd = accept(_listenFd, (struct sockaddr*)&addr, &len);
	if (fd < 0) return;

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

	// Protection against buffer flooding
	if (client->getBuffer().length() > MAX_BUFFER) {
		_sendReply(client, "ERROR :Input buffer overflow\r\n");
		_toRemove.insert(fd);
		return;
	}

	std::string line;
	while (!(line = client->extractLine()).empty()) {
		_processLine(client, line);
		// Client may have been marked for removal by QUIT
		if (_toRemove.count(fd))
			break;
	}
}

void Server::_processLine(Client* client, const std::string& line) {
	if (line.empty()) return;

	std::string rest = line;
	if (rest[0] == ':') {
		size_t sp = rest.find(' ');
		if (sp == std::string::npos) return;
		rest = rest.substr(sp + 1);
	}

	std::vector<std::string> args;
	while (!rest.empty()) {
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

	std::string cmd = _toUpper(args[0]);
	args.erase(args.begin());

	if (cmd == "CAP") return;

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

void Server::_removeClient(int fd) {
	std::map<int, Client*>::iterator cit = _clients.find(fd);
	if (cit == _clients.end()) return;

	std::cout << "Client disconnected (fd " << fd << ")" << std::endl;
	Client* client = cit->second;

	for (std::map<std::string, Channel*>::iterator it = _channels.begin(); it != _channels.end();) {
		if (it->second->isMember(client)) {
			it->second->broadcast(":" + client->getPrefix() + " QUIT :Leaving\r\n", client);
			it->second->removeMember(client);
		}
		if (it->second->memberCount() == 0) {
			delete it->second;
			_channels.erase(it++);
		} else
			++it;
	}

	close(fd);
	delete client;
	_clients.erase(cit);
	for (size_t i = 0; i < _pollfds.size(); i++) {
		if (_pollfds[i].fd == fd) {
			_pollfds.erase(_pollfds.begin() + i);
			break;
		}
	}
}

void Server::_flushRemovals() {
	for (std::set<int>::iterator it = _toRemove.begin(); it != _toRemove.end(); ++it)
		_removeClient(*it);
	_toRemove.clear();
}

void Server::_sendReply(Client* client, const std::string& msg) {
	if (send(client->getFd(), msg.c_str(), msg.length(), 0) < 0)
		_toRemove.insert(client->getFd());
}

void Server::_sendReply(int fd, const std::string& msg) {
	if (send(fd, msg.c_str(), msg.length(), 0) < 0)
		_toRemove.insert(fd);
}

Client* Server::_findClientByNick(const std::string& nick) {
	for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
		if (it->second->getNick() == nick)
			return it->second;
	return NULL;
}

Channel* Server::_getOrCreateChannel(const std::string& name) {
	std::map<std::string, Channel*>::iterator it = _channels.find(name);
	if (it != _channels.end())
		return it->second;
	Channel* ch = new Channel(name);
	_channels[name] = ch;
	return ch;
}

void Server::_welcomeClient(Client* c) {
	std::string nick = c->getNick();
	_sendReply(c, ":ircserv 001 " + nick + " :Welcome to the IRC server, " + c->getPrefix() + "\r\n");
	_sendReply(c, ":ircserv 002 " + nick + " :Your host is ircserv, running version 1.0\r\n");
	_sendReply(c, ":ircserv 003 " + nick + " :This server was created today\r\n");
	_sendReply(c, ":ircserv 004 " + nick + " ircserv 1.0 o itkol\r\n");
}

std::vector<std::string> Server::_split(const std::string& s, char delim) {
	std::vector<std::string> tokens;
	std::istringstream iss(s);
	std::string token;
	while (std::getline(iss, token, delim))
		if (!token.empty())
			tokens.push_back(token);
	return tokens;
}

std::string Server::_toUpper(const std::string& s) {
	std::string r = s;
	for (size_t i = 0; i < r.length(); i++)
		r[i] = std::toupper(r[i]);
	return r;
}
