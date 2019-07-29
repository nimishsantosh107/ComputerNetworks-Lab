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
	int sock_fd = 0, server_fd;
	struct sockaddr_in servaddr;
	int n;
	char buf[MAX],buf1[MAX];

	//CREATE SOCKET
	if ((sock_fd = socket(PF_INET,SOCK_STREAM,0)) <= 0) error("\033[0;31mSOCKET FAILED\033[0m");

	//RESET servaddr / ASSIGN IP, PORT, FAMILY  OF **SERVER**
	bzero(&servaddr, sizeof(servaddr)); 
	if ((inet_aton("127.0.0.1", &servaddr.sin_addr)) == 0) error("\033[0;31mIP ERROR\033[0m");
	servaddr.sin_port = htons(SERVER_PORT); 
	servaddr.sin_family = PF_INET; 

    //CONNECT
	if ((connect(sock_fd, (SA*)&servaddr, sizeof(servaddr))) != 0) error("\033[0;31mCONNECT ERROR\033[0m");
	
	while(1){	
		n=0;
		while ((buf[n++] = getchar()) != '\n') 
			;
		write(sock_fd, buf, sizeof(buf));
		if ((strncmp(buf, "exit", 4)) == 0) { 
			bzero(buf, MAX);
			printf("");
			printf("\033[1;31mCLIENT EXIT\033[0m\n"); 
			break; 
		} 
		bzero(buf, MAX); 
	}

	//CLOSE SOCKET
	close(sock_fd);
	return 0;
}