#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h> 
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h> 
#include <netinet/in.h>
#include <arpa/inet.h>
#define SA struct sockaddr 
#define SERVER_PORT 80
#define MAX 65535

int error(char *msg){
	perror(msg);
	exit(1);
}

int main(int argc, char const *argv[])
{
	char buf[MAX];
	int sock_fd = 0, server_fd;
	struct sockaddr_in servaddr; 

	int byte_count;
	struct addrinfo hints, *res;
    int sockfd;
	hints.ai_family=AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    getaddrinfo("www.google.com","443", &hints, &res);
    sockfd = socket(res->ai_family,res->ai_socktype,res->ai_protocol);
    connect(sockfd,res->ai_addr,res->ai_addrlen);

	//CREATE SOCKET
	//if ((sock_fd = socket(PF_INET,SOCK_STREAM,0)) <= 0) error("\033[0;31mSOCKET FAILED\033[0m");

	//RESET servaddr / ASSIGN IP, PORT, FAMILY  OF **SERVER**
	// bzero(&servaddr, sizeof(servaddr)); 
	// if ((inet_aton("www.google.com", &servaddr.sin_addr)) == 0) error("\033[0;31mIP ERROR\033[0m");
	// servaddr.sin_port = htons(SERVER_PORT); 
	// servaddr.sin_family = PF_INET; 

    //CONNECT
	//if ((connect(sock_fd, (SA*)&servaddr, sizeof(servaddr))) != 0) error("\033[0;31mCONNECT ERROR\033[0m");
	
    //CHAT
	char *header = "GET /index.html HTTPS/1.1\r\nHost: www.google.com\r\n\r\n";
	send(sockfd, header, sizeof(header), 0);
	byte_count = recv(sockfd,buf,sizeof(buf),0);

	printf("%s\n", buf);
    //CLOSE SOCKET
	close(sock_fd);
	return 0;
}