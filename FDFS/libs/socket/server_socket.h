#ifndef __SERVER_SOCKET_H__
#define __SERVER_SOCKET_H__	1

#include <socket.h>
#include <def.h>
#include <sys/time.h>

#define MAX_CONN_NUM	1024

typedef struct Client_Args
{
	sockaddr_in client_addr;
	int sockfd;

} Client_Args;

class Server_Socket {

private:
	int sockfd;
	sockaddr_in server_addr;
	int bufsize;

	timeval timeout;

public:
	Server_Socket(int port);
	~Server_Socket();

	bool create_s();
	bool bind_s();
	bool listen_s();
	bool init();

	bool accept_s(Client_Args *client_args);
	bool send_s(Client_Args *client_args, char *buf);
	int recv_s(Client_Args *client_args, char *buf, int bufsize);

	bool is_valid();
	void set_noneblock(const bool flag);

	int get_sockfd();
	int get_bufsize();
	void set_bufsize(int bufsize);

	millisecond get_timeout();
	void set_timeout(millisecond ms);
};

#endif
