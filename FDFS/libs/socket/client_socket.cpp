#include <cstring>
#include <client_socket.h>

Client_Socket::Client_Socket(char *ip, int port) {
	this->sockfd = -1;

	memset(&(this->remote_addr), 0, sizeof(sockaddr_in));
	this->remote_addr.sin_family = AF_INET;
	this->remote_addr.sin_addr.s_addr = inet_addr(ip);
	this->remote_addr.sin_port = htons(port);

	this->bufsize = DEFAULT_BUFSIZE;

	this->timeout.tv_sec = -1;
	this->timeout.tv_usec = -1;
}

Client_Socket::~Client_Socket() {
	if (this->is_valid()) {
		close(this->sockfd);
	}
}

bool Client_Socket::create_s() {
	if ((this->sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		this->sockfd = -1;
		return false;
	}
	return true;
}

bool Client_Socket::connect_s() {
	if (!(this->is_valid())) {
		return false;
	}
	if (connect(this->sockfd, (struct sockaddr *)(&(this->remote_addr)), sizeof(sockaddr)) < 0) {
		return false;
	}
	return true;
}

bool Client_Socket::init() {
	if (!((this->create_s()) && (this->connect_s()))) {
		return false;
	}
	return true;
}

bool Client_Socket::send_s(char *buf) {
	int len = strlen(buf);
	if (send(this->sockfd, buf, len, 0) < 0) {
		return false;
	}
	return true;
}

bool Client_Socket::recv_s(char *buf, int bufsize) {
	memset(buf, 0, bufsize);
	int len = recv(this->sockfd, buf, bufsize, 0);
	buf[len] = '\0';
	return len;
}

bool Client_Socket::is_valid() {
	return (this->sockfd >= 0);
}

void Client_Socket::set_noneblock(const bool flag) {
	if(this->is_valid()) {
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
}

int Client_Socket::get_sockfd() {
	return this->sockfd;
}

int Client_Socket::get_bufsize() {
	return this->bufsize;
}

void Client_Socket::set_bufsize(int bufsize) {
	this->bufsize = bufsize;
}

millisecond Client_Socket::get_timeout() {
	return this->timeout.tv_sec * 1000 + this->timeout.tv_usec / 1000;
}

void Client_Socket::set_timeout(millisecond ms) {
	time_t sec = ms / 1000;
	this->timeout.tv_sec = sec;
	this->timeout.tv_usec = (ms - sec * 1000) * 1000;

	if (this->is_valid()) {
		setsockopt(this->sockfd, SOL_SOCKET, SO_SNDTIMEO, &(this->timeout), sizeof(timeval));
	}
}
