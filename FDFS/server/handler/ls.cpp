#include <ls.h>
#include <cstring>

Command_LS::Command_LS(Client_Args client_args, Server_Socket *server_socket, char *path): Command_Handler(client_args, server_socket) {
	strcpy(this->path, path);
	return;
}

Command_LS::~Command_LS() {
	return;
}

void Command_LS::handler() {
	char *dest = NULL;
	data_dictionary->get_subdir_and_file(dest, this->path);
	this->server_socket->send_s(&(this->client_args), dest);
	delete[] dest;
}
