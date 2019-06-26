#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define SA struct sockaddr 
#define PORT 4000
#define MAX 256

int error(char *msg){
	perror(msg);
	exit(1);
}

int main(int argc, char const *argv[]){
	//DECLARATIONS
	int server_fd;
	struct sockaddr_in servaddr; 	

	//CREATE SOCKET
	if ((server_fd = socket(PF_INET,SOCK_STREAM,0)) < 1) error("SOCKET FAILED");

	//RESET servaddr / ASSIGN IP, PORT, FAMILY 
	bzero(&servaddr, sizeof(servaddr)); 
	if ((inet_aton("127.0.0.1", &servaddr.sin_addr)) == 0) error("IP ERROR");
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_family = AF_INET; 

    //BIND TO PORT
    if ((bind(server_fd, (SA*)&servaddr, sizeof(servaddr))) != 0) error("BIND ERROR");

    //LISTEN ON PORT
    if ((listen(server_fd, 5)) != 0) error("LISTEN ERROR");

	//CLOSE SOCKET
	close(server_fd);
	return 0;
}