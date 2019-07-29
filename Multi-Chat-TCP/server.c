#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
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
	int server_fd, client_fd , sel_sd;
	int clients[3];
	struct sockaddr_in servaddr, clientaddr;
	int n;
	char buf[MAX];
	fd_set readfds;

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

	while(1){
		FD_ZERO(&readfds);
		FD_SET(server_fd, &readfds);
		sel_sd = server_fd;
		for (int i = 0; i < 3; i++) {
			int sd = = clients[i];
			if(sd > 0) FD_SET(sd, &readfds);
			if(sd > sel_sd) sel_sd = sd;
		}
		int activity = select(selsd+1, &readfds, NULL, NULL, NULL);
		if(FD_ISSET(server_fd , &readfds)) {
			if ((client_fd = accept(server_fd, (SA*)&clientaddr, &len)) <= 0) error("\033[0;31mACCEPT ERROR\033[0m");
			for (int i = 0; i < 5; i++){
				if (clients[i] == 0) {
					clients[i] = client_fd;
					break;
				}
			}
		}
		for(int i = 0; i<5; i++) {
			if(FD_ISSET(clients[i], &readfds)) {
				read(clients[i], buf, MAX);
				if(buff[0] == "*") {
					close(clients[i]);
					clients[i] = 0;
					printf("CLIENT CLOSED\n");
				}else {
					printf("CLIENT %d: %s\n", i, buf );
				}
				bzero(buf, MAX);
			}
		}
	}

	//CLOSE SOCKET
	close(server_fd);
	return 0;
}