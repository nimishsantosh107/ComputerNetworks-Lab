#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

int main(int argc, char const *argv[]){
	int server_fd;
	struct sockaddr_in address; 	
	char buffer[1024] = {0}; 

	//CREATE SOCKET
	if((server_fd = socket(PF_INET,SOCK_STREAM,0)) == 0){
		perror("SOCKET FAILED");
		exit(1);
	}
	printf("%d\n",server_fd);

	//CLOSE SOCKET
	close(server_fd);
	return 0;
}