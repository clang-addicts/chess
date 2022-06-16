#include "network.h"

char buffer[4096] = "Hello, World!";
#define PORT 9000

void* network_find_opponet() {
    printf("find net opponet!\n");   
    return NULL;
}

#if 0
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
#else
void wait_for_opponet()
{
	SOCKET server_socket = INVALID_SOCKET;
	SOCKET client_socket = INVALID_SOCKET;
	struct sockaddr_in service;
	WSADATA wsaData;

	// https://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-wsastartup
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR) {
        wprintf(L"Error at WSAStartup()\n");
        return;
    }

	// https://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-socket
	server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (server_socket == INVALID_SOCKET) {
		log(LOG_ERR, "socket() failed %d", WSAGetLastError());
		WSACleanup();
		return;
	}

	service.sin_family = AF_INET;
	service.sin_addr.s_addr = inet_addr("127.0.0.1");
	service.sin_port = htons(PORT);

	// https://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-bind
	if(bind(server_socket, (SOCKADDR*) &service, sizeof(service)) == SOCKET_ERROR) {
		log(LOG_ERR, "bind() failed %d", WSAGetLastError());
		goto err;
	}

	// https://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-listen
	log(LOG_DEBUG, "listening...");
	if(listen(server_socket, SOMAXCONN) == SOCKET_ERROR) {
		log(LOG_ERR, "listen() failed %d", WSAGetLastError());
		goto err;	
	}

	// https://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-accept
	log(LOG_DEBUG, "accepting...");
	client_socket = accept(server_socket, NULL, NULL);
	if(client_socket == INVALID_SOCKET) {
		log(LOG_ERR, "accept() failed %d", WSAGetLastError());
		goto err;	
	}

err:
	log(LOG_DEBUG, "closing...");
	if(closesocket(server_socket)==SOCKET_ERROR) {
		log(LOG_ERR, "closesocket() failed %d", WSAGetLastError());
		return;
	}
	WSACleanup();
}

void join_as_opponet()
{
	SOCKET client_socket = INVALID_SOCKET;
	struct sockaddr_in service;
	WSADATA wsaData;

	// https://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-wsastartup
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR) {
        wprintf(L"Error at WSAStartup()\n");
        return;
    }

	// https://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-socket
	client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (client_socket == INVALID_SOCKET) {
		log(LOG_ERR, "socket() failed %d", WSAGetLastError());
		WSACleanup();
		return;
	}

	service.sin_family = AF_INET;
	service.sin_addr.s_addr = inet_addr("127.0.0.1");
	service.sin_port = htons(PORT);

	// https://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-bind
	if(bind(server_socket, (SOCKADDR*) &service, sizeof(service)) == SOCKET_ERROR) {
		log(LOG_ERR, "bind() failed %d", WSAGetLastError());
		goto err;
	}

	// https://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-listen
	log(LOG_DEBUG, "listening...");
	if(listen(server_socket, SOMAXCONN) == SOCKET_ERROR) {
		log(LOG_ERR, "listen() failed %d", WSAGetLastError());
		goto err;	
	}

	// https://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-accept
	log(LOG_DEBUG, "accepting...");
	client_socket = accept(server_socket, NULL, NULL);
	if(client_socket == INVALID_SOCKET) {
		log(LOG_ERR, "accept() failed %d", WSAGetLastError());
		goto err;	
	}

err:
	log(LOG_DEBUG, "closing...");
	if(closesocket(server_socket)==SOCKET_ERROR) {
		log(LOG_ERR, "closesocket() failed %d", WSAGetLastError());
		return;
	}
	WSACleanup();
}

#endif // 0