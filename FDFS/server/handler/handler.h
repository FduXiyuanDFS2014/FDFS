#ifndef __HANDLER_H__
#define __HANDLER_H__	1

#include <server_socket.h>
#include <dictionary.h>

class Command_Handler {

protected:
	Client_Args client_args;
	Server_Socket *server_socket;

	char *cmd_buf;

public:
	Command_Handler(Client_Args client_args, Server_Socket *server_socket);
	virtual ~Command_Handler();

	virtual void handler() = 0;
};

#endif
