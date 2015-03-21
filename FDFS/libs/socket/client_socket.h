#ifndef __CLIENT_SOCKET_H__
#define __CLIENT_SOCKET_H__	1

#include <socket.h>
#include <def.h>
#include <sys/time.h>

class Client_Socket {

private:
	int sockfd;
	sockaddr_in remote_addr;
	int bufsize;

	timeval timeout;

public:
	Client_Socket(char *ip, int port);
	~Client_Socket();

	bool create_s();
	bool connect_s();
	bool init();

	bool send_s(char *buf);
	bool recv_s(char *buf, int bufsize);

	bool is_valid();
	void set_noneblock(const bool flag);

	int get_sockfd();
	int get_bufsize();
	void set_bufsize(int bufsize);

	millisecond get_timeout();
	void set_timeout(millisecond ms);
};

#endif
