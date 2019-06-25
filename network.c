#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
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
	if((server_fd = socket(PF_INET,SOCK_STREAM,0)) == 0)
		error("SOCKET FAILED");

	//RESET servaddr / ASSIGN IP, PORT, FAMILY 
	bzero(&servaddr, sizeof(servaddr)); 
	if((inet_aton("192.168.1.7", &servaddr.sin_addr)) == 0)
		error("IP ERROR");
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_family = AF_INET; 
    
    //check
    printf("%d\n%d\n",servaddr.sin_addr.s_addr,servaddr.sin_port);



	//CLOSE SOCKET
	close(server_fd);
	return 0;
}