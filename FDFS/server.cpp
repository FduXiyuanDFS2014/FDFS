#include <iostream>
#include <cstring>

#include <server_socket.h>

int ssmain() {
	Server_Socket server_socket(23333);
	if (!(server_socket.init())) {
		return -1;
	}
	Client_Args client_args;
	char buf[DEFAULT_BUFSIZE];
	server_socket.accept_s(&client_args);
	strcpy(buf, "Welcome to Server!");
	server_socket.send_s(&client_args, buf);
	server_socket.recv_s(&client_args, buf, DEFAULT_BUFSIZE);
	int i = 0;
	for ( ; buf[i]; ++i) {
		char c = buf[i];
		if (c >= 'a' && c <= 'z') {
			buf[i] = c + 'A' - 'a';
		}
	}
	server_socket.send_s(&client_args, buf);
	return 0;
}
