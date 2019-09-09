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
#define SERVER_PORT 4000
#define MAX 256

typedef struct node {
	char domain[MAX];
	char ip[MAX];
	struct node *next;
} Node;

Node* head = NULL;

Node* insert( Node *head, char domain[], char ip[]) {
	Node *temp = head;
	Node *new = (Node*) malloc (sizeof(Node));
	strcpy(new->domain, domain);
	strcpy(new->ip, ip);
	new->next = NULL;
	if(head == NULL){ head = new; }
	else{
		new->next = head;
		head = new;
	}
	return head;
} 

int error(char *msg){
	perror(msg);
	exit(1);
}

int main(int argc, char const *argv[])
{	
	int bytecount;
	char buf[MAX];
	char buf2[MAX];
	int server_fd;
	struct sockaddr_in servaddr, clientaddr;
	
	//CREATE SOCKET
	if ((server_fd = socket(PF_INET, SOCK_DGRAM, 0)) <= 0) error("\033[0;31mSOCKET ERROR\033[0m");

	//CLEAR servaddr / SET IP,PORT,FAMILY OF SERVER
	bzero(&servaddr , sizeof(servaddr));
	if((inet_aton("127.0.0.1", &servaddr.sin_addr)) == 0) error("\033[0;31mIP ERROR\033[0m");
	servaddr.sin_port = htons(SERVER_PORT);
	servaddr.sin_family = PF_INET;

	//BIND 
	if((bind(server_fd, (SA*)&servaddr, sizeof(servaddr))) !=0 ) error("\033[0;31mBIND ERROR\033[0m");
	printf("\033[1;36mDNS SERVER WAITING ON PORT 4000\033[0m\n\n");

	while(1){
		//RECIEVE DATA
		unsigned int len = sizeof(clientaddr);
		bytecount = recvfrom(server_fd, &buf, MAX, MSG_WAITALL, (SA*)&clientaddr, &len);

		//EXTRA FOR NS LOOKUP
		int found = 0;
		for(Node* temp = head; temp != NULL; temp = temp->next){
			if(strcmp(temp->domain,buf) == 0){
				strcpy(buf2,temp->ip);
				found = 1;
				break;
			}
		}
		printf("FOUND %d\n",found );
		if(found == 0) {
			struct hostent *getAddr = gethostbyname(buf);
			struct in_addr **addrlist = (struct in_addr **)getAddr->h_addr_list;
			char *hostaddress = inet_ntoa(*addrlist[0]);
			head = insert(head, buf, hostaddress);
			strcpy(buf2, hostaddress);
		}

		//REPLACE SENDING BUF WITH IP ADDRESS

		sendto(server_fd, buf2, MAX, MSG_WAITALL, (SA*)&clientaddr, sizeof(clientaddr));
		printf("LOG: %s\t",buf);
		printf("RES: %s\n",buf2);
		bzero(buf, MAX); 
		bzero(buf2, MAX);
	}

	//CLOSE SOCKET
	close(server_fd);
	return 0;
}