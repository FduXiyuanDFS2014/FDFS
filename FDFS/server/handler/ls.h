#ifndef __LS_H__
#define __LS_H__	1

#include <handler.h>

class Command_LS: public Command_Handler {

private:
	char path[MAX_PATH_LEN];

public:
	Command_LS(Client_Args client_args, Server_Socket *server_socket, char *path);
	~Command_LS();

	void handler();
};

#endif
