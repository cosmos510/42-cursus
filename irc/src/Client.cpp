#include "Client.hpp"

Client::Client(int fd) : _fd(fd), _passwd(false), _nickSet(false), _userSet(false) {}

Client::~Client() {}

int Client::getFd() const { return _fd; }
std::string Client::getNick() const { return _nick; }
std::string Client::getUser() const { return _user; }
std::string Client::getRealname() const { return _realname; }
std::string Client::getHost() const { return _host; }
std::string& Client::getBuffer() { return _buffer; }
bool Client::hasPasswd() const { return _passwd; }
bool Client::hasNick() const { return _nickSet; }
bool Client::hasUser() const { return _userSet; }
bool Client::isRegistered() const { return _passwd && _nickSet && _userSet; }

std::string Client::getPrefix() const {
	return _nick + "!" + _user + "@" + _host;
}

void Client::setNick(const std::string& nick) { _nick = nick; _nickSet = true; }
void Client::setUser(const std::string& user) { _user = user; _userSet = true; }
void Client::setRealname(const std::string& realname) { _realname = realname; }
void Client::setHost(const std::string& host) { _host = host; }
void Client::setPasswd(bool val) { _passwd = val; }

void Client::appendBuffer(const std::string& data) { _buffer += data; }

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
