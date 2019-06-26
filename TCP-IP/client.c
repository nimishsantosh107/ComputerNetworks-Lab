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

void chat(int sock_fd){
	char buf[MAX];
	
	while(1){
		printf("You: ");
		scanf("%[^\n]s",buf);
		write(sock_fd, buf, sizeof(buf));
		bzero(buf, sizeof(buf));
		printf("Server: ");
		read(sock_fd ,&buf, MAX);
		printf("%s\n", buf);
	}
}

int main(int argc, char const *argv[])
{
	//DECLARATIONS
	int sock_fd = 0, server_fd;
	struct sockaddr_in servaddr; 

	//CREATE SOCKET
	if ((sock_fd = socket(PF_INET,SOCK_STREAM,0)) <= 0) error("SOCKET FAILED");

	//RESET servaddr / ASSIGN IP, PORT, FAMILY  OF **SERVER**
	bzero(&servaddr, sizeof(servaddr)); 
	if ((inet_aton("127.0.0.1", &servaddr.sin_addr)) == 0) error("IP ERROR");
    servaddr.sin_port = htons(SERVER_PORT); 
    servaddr.sin_family = PF_INET; 

    //CONNECT
    if ((connect(sock_fd, (SA*)&servaddr, sizeof(servaddr))) != 0) error("CONNECT ERROR");
    chat(sock_fd);

    //CLOSE SOCKET
    close(sock_fd);
	return 0;
}