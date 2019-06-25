# Notes:

## Steps:
* CREATE SOCKET
* SET SERVERADDR STRUCT


## Notes:
### Ways to set IP address in servaddr STRUCT:
*   servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
*	if((inet_aton("192.168.1.x", &servaddr.sin_addr)) == 0) error("IP ERROR");
*   servaddr.sin_addr.s_addr = inet_addr("192.168.1.x");