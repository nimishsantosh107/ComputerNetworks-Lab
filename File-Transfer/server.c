#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#define SA struct sockaddr 
#define SERVER_PORT 4000
#define MAX 256

int error(char *msg){
	perror(msg);
	exit(1);
}

int main(int argc, char const *argv[])
{
	int bc;
	char fileBuf[MAX],buf[MAX];
	int server_fd, client_fd, fd;
	struct sockaddr_in servaddr, clientaddr;	

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

	//GET FILE NAME
	read(client_fd, buf, MAX);
	printf("FILE REQUESTED: %s\n",buf );

	//OPEN FILE
	if((fd = open(buf,O_RDONLY)) <= 0) error("\033[0;31mFILE OPEN ERROR\033[0m");

	//READ FILE
	read(fd, fileBuf, MAX);
	write(client_fd, fileBuf, MAX);

	//CLOSE
	bzero(buf, MAX); 
	bzero(fileBuf, MAX); 
	close(server_fd);	
	return 0;
}