#ifndef __SERVER_CMD_HANDLE_H__
#define __SERVER_CMD_HANDLE_H__	1

#include <server_socket.h>
#include <thread.h>
#include <cmd.h>

class Server_CMD_Handle: public Thread {

private:
	Client_Args client_args;
	Server_Socket *server_socket;

	char *cmd_buf;

public:
	Server_CMD_Handle(Client_Args client_args, Server_Socket *server_socket);
	~Server_CMD_Handle();

	void run();

private:
	void call(char *argv[], int argc);
};

#endif
