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
	int server_fd, client_fd;
	struct sockaddr_in servaddr, clientaddr;
	int n;
	char buf[MAX],buf1[MAX];

	//CREATE SOCKET
	if ((server_fd = socket(PF_INET,SOCK_STREAM,0)) <= 0) error("\033[0;31mSOCKET FAILED\033[0m");

	//RESET servaddr / ASSIGN IP, PORT, FAMILY 
	bzero(&servaddr, sizeof(servaddr)); 
	if ((inet_aton("127.0.0.1", &servaddr.sin_addr)) == 0) error("\033[0;31mIP ERROR\033[0m");
	servaddr.sin_port = htons(SERVER_PORT); 
	servaddr.sin_family = PF_INET; 

    //BIND TO PORT
	if ((bind(server_fd, (SA*)&servaddr, sizeof(servaddr))) != 0) error("\033[0;31mBIND ERROR\033[0m");

    //LISTEN ON PORT
	if ((listen(server_fd, 5)) != 0) error("\033[0;31mLISTEN ERROR\033[0m");
	printf("\033[1;36mSERVER LISTENING ON PORT 4000\033[0m\n\n");

    //ACCEPT CONNECTION
	unsigned int len = sizeof(clientaddr);
	if ((client_fd = accept(server_fd, (SA*)&clientaddr, &len)) <= 0) error("\033[0;31mACCEPT ERROR\033[0m"); 

	int pid = fork();
	if(pid > 0){
		while(1){
			read(client_fd, buf1, sizeof(buf1));
			if ((strncmp(buf1, "exit", 4)) == 0) { 
				bzero(buf1, MAX); 
				printf("\033[1;31mCLIENT EXIT\033[0m\n"); 
				break; 
			} 
			printf("\033[1;34mCLIENT:\033[0m %s", buf1);
			bzero(buf1, MAX);
		}
	}
	else{
		while(1){	
			n=0;
			while ((buf[n++] = getchar()) != '\n') 
				;
			write(client_fd, buf, sizeof(buf));
			if ((strncmp(buf, "exit", 4)) == 0) { 
				bzero(buf, MAX);
				printf("");
				printf("\033[1;31mSERVER EXIT\033[0m\n"); 
				break; 
			} 
			bzero(buf, MAX); 
		}
	}

	//CLOSE SOCKET
	close(server_fd);
	return 0;
}