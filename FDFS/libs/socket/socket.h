#ifndef __SOCKET_H__
#define __SOCKET_H__	1

#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define DEFAULT_BUFSIZE 4096

typedef struct sockaddr		sockaddr;
typedef struct sockaddr_in 	sockaddr_in;
typedef struct timeval		timeval;

#endif
