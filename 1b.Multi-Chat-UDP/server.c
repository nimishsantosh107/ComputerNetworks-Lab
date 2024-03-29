#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define SA struct sockaddr
#define SERVER_PORT 5000
#define MAX 256

int error(char *msg){
	perror(msg);
	exit(1);
}

int main(int argc, char const *argv[])
{
	int bytecount;
	char buf[MAX];
	int server_fd;
	struct sockaddr_in servaddr, clientaddr;
	
	//CREATE SOCKET
	if ((server_fd = socket(PF_INET, SOCK_DGRAM, 0)) <= 0) error("SOCKET ERROR");

	//CLEAR servaddr / SET IP,PORT,FAMILY OF SERVER
	bzero(&servaddr , sizeof(servaddr));
	if((inet_aton("127.0.0.1", &servaddr.sin_addr)) == 0) error("IP ERROR");
	servaddr.sin_port = htons(SERVER_PORT);
	servaddr.sin_family = PF_INET;

	//BIND 
	if((bind(server_fd, (SA*)&servaddr, sizeof(servaddr))) !=0 ) error("BIND ERROR");
	printf("SERVER WAITING ON PORT 4000\n\n");

	while(1){
		//RECIEVE DATA
		unsigned int len = sizeof(clientaddr);
		bytecount = recvfrom(server_fd, buf, MAX, MSG_WAITALL, (SA*)&clientaddr, &len);
		buf[bytecount] = '\0';
		sendto(server_fd, buf , MAX, MSG_DONTWAIT, (SA*)&clientaddr, sizeof(clientaddr));
		printf("LOG: %s", buf);
		bzero(buf, MAX); 
	}

	//CLOSE SOCKET
	close(server_fd);
	return 0;
}