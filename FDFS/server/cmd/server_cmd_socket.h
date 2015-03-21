#ifndef __Server_CMD_SOCKET_H__
#define __Server_CMD_SOCKET_H__	1

#include <thread.h>
#include <server_socket.h>

class Server_CMD_Socket: Thread {

private:
	Server_Socket *server_cmd_socket;

public:
	Server_CMD_Socket(int port);
	~Server_CMD_Socket();

	bool init();

	void run();
};

#endif
