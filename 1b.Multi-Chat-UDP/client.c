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
	int sock_fd;
	struct sockaddr_in servaddr;
	char buf[MAX];
	int n,bytecount;

	//CREATE SOCKET
	if((sock_fd = socket(PF_INET, SOCK_DGRAM, 0)) <= 0) error("SOCKET ERROR");

	//CLEAR servaddr / SET IP,PORT,FAMILY OF SERVER
	bzero(&servaddr , sizeof(servaddr));
	if((inet_aton("127.0.0.1", &servaddr.sin_addr)) == 0) error("IP ERROR");
	servaddr.sin_port = htons(SERVER_PORT);
	servaddr.sin_family = PF_INET;

	int pid = fork();
	if(pid > 0){
		//SEND MESSAGE
		while(1){
			n=0;
			while ((buf[n++] = getchar()) != '\n') 
				;
			sendto(sock_fd, buf , MAX, MSG_DONTWAIT, (SA*)&servaddr, sizeof(servaddr));
			bzero(buf, MAX); 
		}
	}else{
		while(1){
			unsigned int len = sizeof(servaddr);
			bytecount = recvfrom(sock_fd, &buf, MAX, MSG_DONTWAIT, (SA*)&servaddr, &len);
			buf[bytecount] = '\0';
			printf("%s", buf);
			bzero(buf, MAX); 
		}
	}
	//CLOSE SOCKET
	close(sock_fd);
	return 0;
}