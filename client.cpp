#include <iostream>

#include <client_socket.h>

using namespace std;

int main() {
	char buf[DEFAULT_BUFSIZE];
	char ip[] = "192.168.0.108";
	Client_Socket client_socket(ip, 23333);
	if (!(client_socket.init())) {
		return -1;
	}
	client_socket.recv_s(buf, DEFAULT_BUFSIZE);
	cout << buf << endl;
	cin >> buf;
	client_socket.send_s(buf);
	client_socket.recv_s(buf, DEFAULT_BUFSIZE);
	cout << buf << endl;
	return 0;
}
