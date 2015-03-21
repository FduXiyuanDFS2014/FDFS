#include <handler.h>

Command_Handler::Command_Handler(Client_Args client_args, Server_Socket *server_socket) {
	this->client_args.client_addr = client_args.client_addr;
	this->client_args.sockfd = client_args.sockfd;

	this->server_socket = server_socket;
	this->cmd_buf = new char[server_socket->get_bufsize()];
}

Command_Handler::~Command_Handler() {
	return;
}
