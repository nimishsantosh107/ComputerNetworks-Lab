#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define SA struct sockaddr
#define SERVER_PORT 4000
#define MAX 256

int error(char *msg){
	perror(msg);
	exit(1);
}

int main(int argc, char const *argv[])
{
	int sock_fd, server_fd;
	struct sockaddr_in serveraddr;

	//CREATE SOCKET
	if((sock_fd = socket(PF_INET, SOCK_DGRAM, 0)) <= 0) error("SOCKET ERROR");


	//CLOSE SOCKET
	close(sock_fd);
	return 0;
}