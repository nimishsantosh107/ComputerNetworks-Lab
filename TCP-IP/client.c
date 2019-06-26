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
	int n;
	char buf[MAX];
	
	while(1){
		//MESSAGE
		printf("YOU: ");
		n=0;
		while ((buf[n++] = getchar()) != '\n')
			;
 		write(sock_fd, buf, sizeof(buf));
		if ((strncmp(buf, "exit", 4)) == 0) { 
			bzero(buf, MAX);
            printf("CLIENT EXIT\n"); 
            break; 
        } 
		bzero(buf, MAX);
		//RESPONSE FROM SERVER
		read(sock_fd ,&buf, sizeof(buf));
		if ((strncmp(buf, "exit", 4)) == 0) { 
			bzero(buf, MAX);
            printf("SERVER EXIT\n"); 
            break; 
        } 
		printf("SERVER: %s\n", buf);
		bzero(buf, MAX);
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
    
    //CHAT
    chat(sock_fd);

    //CLOSE SOCKET
    close(sock_fd);
	return 0;
}