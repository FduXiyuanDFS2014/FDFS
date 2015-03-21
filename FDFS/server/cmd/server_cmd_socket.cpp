#include <server_cmd_socket.h>

Server_CMD_Socket::Server_CMD_Socket(int port) {
	this->server_cmd_socket = new Server_Socket(port);
}

Server_CMD_Socket::~Server_CMD_Socket() {
	delete this->server_cmd_socket;
}

bool Server_CMD_Socket::init() {
	this->server_cmd_socket->create_s();
	this->server_cmd_socket->set_timeout(3000);
	this->server_cmd_socket->bind_s();
	this->server_cmd_socket->listen_s();
	return this->server_cmd_socket->is_valid();
}

void Server_CMD_Socket::run() {
	while (true) {
		Client_Args client_args;
		this->server_cmd_socket->accept_s(&client_args);

		// to handle
	}
}
