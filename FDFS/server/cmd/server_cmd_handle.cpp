#include <server_cmd_handle.h>
#include <stringlib.h>
#include <cstring>

Server_CMD_Handle::Server_CMD_Handle(Client_Args client_args, Server_Socket *server_socket) {
	this->client_args.client_addr = client_args.client_addr;
	this->client_args.sockfd = client_args.sockfd;

	this->server_socket = server_socket;
	this->cmd_buf = new char[server_socket->get_bufsize()];
}

Server_CMD_Handle::~Server_CMD_Handle() {
	delete []this->cmd_buf;
}

void Server_CMD_Handle::run() {
	int bufsize = this->server_socket->get_bufsize();
	while (true) {
		memset(this->cmd_buf, 0, bufsize);
		int len = this->server_socket->recv_s(&(this->client_args), this->cmd_buf, bufsize);
		if (len <= 0) {
			continue;
		}
		char *argv[4];
		int argc = parse_args(argv, this->cmd_buf, len);
		this->call(argv, argc);
	}
}

void Server_CMD_Handle::call(char *argv[], int argc) {
	char *op = argv[0];
	switch(argc) {
	case 2:
		if (strcmp(op, _LS) == 0) {
			// TODO ls();
		} else if (strcmp(op, _GET) == 0) {
			// TODO get();
		} else if (strcmp(op, _PUT) == 0) {
			// TODO put();
		}
		break;
	case 3:
		if (strcmp(op, _LS) == 0) {
			// TODO ls();
		}
		break;
	default:
		return;
	}
}



















