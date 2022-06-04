#include "network.h"

void* network_find_opponet() {
    printf("find net opponet!\n");   
    return NULL;
}
/*
char buffer[4096] = "Hello, World!";
#define PORT 9000


void wait_for_opponet()
{
	int c_socket, s_socket;
	struct sockaddr_in s_addr;
	struct sockaddr_in c_addr;
	int len;
	int n;
	
	//SOCKET SETTINGS FOR A TCP TYPE SOCKET
	s_socket = socket(PF_INET,SOCK_STREAM,0);
	//Sets all s_addr value to 0
	memset(&s_addr, 0, sizeof(s_addr));
	
	//Setting Request Acception Settings
	//PORT: 9000
	//IP: ANY IP SET TO MY COMPUTER
	//IPV4
	s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	s_addr.sin_family = AF_INET;
	s_addr.sin_port = htons(PORT);

	//Binds socket to the port/address/whatever more
	if(bind(s_socket, (struct sockaddr*) &s_addr, sizeof(s_addr))==-1){
		printf("CANNOT BIND\n");
		return -1;
	}

		
	if(listen(s_socket,5)==-1){
		printf("listen fail\n");
		return -1;
	}
	
	while(1){
		len = sizeof(c_addr);
		c_socket=accept(s_socket,(struct sockaddr*)&c_addr, &len);
		
		n = strlen(buffer);
		write(c_socket,buffer,n);
		
		close(c_socket);
	}
	close(s_socket);
}
*/