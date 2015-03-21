#include <cstring>
#include <server_socket.h>

Server_Socket::Server_Socket(int port) {
	this->sockfd = -1;

	memset(&(this->server_addr), 0, sizeof(sockaddr_in));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(port);

	this->bufsize = DEFAULT_BUFSIZE;

	this->timeout.tv_sec = -1;
	this->timeout.tv_usec = -1;
}

Server_Socket::~Server_Socket() {
	if (this->is_valid()) {
		close(this->sockfd);
	}
}

bool Server_Socket::create_s() {
	if ((this->sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		this->sockfd = -1;
		return false;
	}
	return true;
}

bool Server_Socket::bind_s() {
	if (!(this->is_valid())) {
		return false;
	}
	if (bind(this->sockfd, (sockaddr *)&(this->server_addr), sizeof(sockaddr)) < 0) {
        return false;
    }
    return true;
}

bool Server_Socket::listen_s() {
	if (!is_valid()) {
		return false;
	}
	if (listen(this->sockfd, MAX_CONN_NUM) < 0) {
		return false;
	}
	return true;
}

bool Server_Socket::init() {
	if (!((this->create_s()) && (this->bind_s()) && (this->listen_s()))) {
		return false;
	}
	return true;
}

bool Server_Socket::accept_s(Client_Args *client_args) {
	if (!(this->is_valid())) {
		return false;
	}
	int sin_size = sizeof(client_args->client_addr);
	int client_sockfd = accept(this->sockfd, (sockaddr *)&(client_args->client_addr), (socklen_t *)&sin_size);
	if (client_sockfd < 0) {
		return false;
	}
	client_args->sockfd = client_sockfd;
	return true;
}

bool Server_Socket::send_s(Client_Args *client_args, char *buf) {
	int client_sockfd = client_args->sockfd;
	int len = strlen(buf);
	if (send(client_sockfd, buf, len, 0) < 0) {
		return false;
	}
	return true;
}

int Server_Socket::recv_s(Client_Args *client_args, char *buf, int bufsize) {
	memset(buf, 0, bufsize);
	int client_sockfd = client_args->sockfd;
	int len = recv(client_sockfd, buf, bufsize, 0);
	buf[len] = '\0';
	return len;
}

bool Server_Socket::is_valid() {
	return (this->sockfd >= 0);
}

void Server_Socket::set_noneblock(const bool flag) {
	if (!(this->is_valid())) {
		return;
	}
	int opts = fcntl(this->sockfd, F_GETFL);
	if (opts < 0) {
		return;
	}
	if (flag) {
		opts = (opts | O_NONBLOCK);
	} else {
		opts = (opts & ~O_NONBLOCK);
	}
	fcntl(this->sockfd, F_SETFL, opts);
}

int Server_Socket::get_sockfd() {
	return this->sockfd;
}

int Server_Socket::get_bufsize() {
	return this->bufsize;
}

void Server_Socket::set_bufsize(int bufsize) {
	this->bufsize = bufsize;
}

millisecond Server_Socket::get_timeout() {
	return this->timeout.tv_sec * 1000 + this->timeout.tv_usec / 1000;
}

void Server_Socket::set_timeout(millisecond ms) {
	time_t sec = ms / 1000;
	this->timeout.tv_sec = sec;
	this->timeout.tv_usec = (ms - sec * 1000) * 1000;

	if (this->is_valid()) {
		setsockopt(this->sockfd, SOL_SOCKET, SO_SNDTIMEO, &(this->timeout), sizeof(timeval));
	}
}
