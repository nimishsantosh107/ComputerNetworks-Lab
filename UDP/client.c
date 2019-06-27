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
	int sock_fd;
	struct sockaddr_in servaddr;
	char *message = "message from client";

	//CREATE SOCKET
	if((sock_fd = socket(PF_INET, SOCK_DGRAM, 0)) <= 0) error("\033[0;31mSOCKET ERROR\033[0m");

	//CLEAR servaddr / SET IP,PORT,FAMILY OF SERVER
	bzero(&servaddr , sizeof(servaddr));
	if((inet_aton("127.0.0.1", &servaddr.sin_addr)) == 0) error("\033[0;31mIP ERROR\033[0m");
	servaddr.sin_port = htons(SERVER_PORT);
	servaddr.sin_family = PF_INET;

	//SEND MESSAGE
	sendto(sock_fd, message , MAX, MSG_DONTROUTE, (SA*)&servaddr, sizeof(servaddr));

	//CLOSE SOCKET
	close(sock_fd);
	return 0;
}