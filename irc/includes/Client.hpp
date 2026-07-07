#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>

class Client {
public:
	Client(int fd);
	~Client();

	int getFd() const;
	std::string getNick() const;
	std::string getUser() const;
	std::string getRealname() const;
	std::string getHost() const;
	std::string getPrefix() const;
	std::string& getBuffer();
	bool isRegistered() const;
	bool hasPasswd() const;
	bool hasNick() const;
	bool hasUser() const;

	void setNick(const std::string& nick);
	void setUser(const std::string& user);
	void setRealname(const std::string& realname);
	void setHost(const std::string& host);
	void setPasswd(bool val);
	void appendBuffer(const std::string& data);
	std::string extractLine();

private:
	int _fd;
	std::string _nick;
	std::string _user;
	std::string _realname;
	std::string _host;
	std::string _buffer;
	bool _passwd;
	bool _nickSet;
	bool _userSet;
};

#endif
