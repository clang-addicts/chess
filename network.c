#include "network.h"

char buffer[4096] = "Hello, World!";
#define PORT 9000

/////////////////////////////// SERVER
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"
/////////////////////////////// SERVER

/////////////////////////////// CLIENT
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"
/////////////////////////////// CLIENT

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
#if 0
	SOCKET server_socket = INVALID_SOCKET;
	SOCKET client_socket = INVALID_SOCKET;
	struct sockaddr_in service;
	WSADATA wsaData;

	log(LOG_DEBUG, "wait opponet starting");

	// https://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-wsastartup
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR) {
		log(LOG_ERR, "WSAStartup() failed");
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

    // Receive until the peer closes the connection
	// https://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-send
	int res = 1;
    do {
		char recvbuf[512] = {0};
		log(LOG_DEBUG, "recving...");
		res = recv(client_socket, recvbuf, (int)strlen(recvbuf), 0);
        if ( res> 0 ) {
			log(LOG_ERR, "Bytes received: %d, msg:%s", res, recvbuf);
		}else if (res == 0) {
			log(LOG_ERR, "Bytes received: %d, msg:%s", res, recvbuf);
			log(LOG_ERR, "Connection closed" );
		}else{
			log(LOG_ERR, "recv failed with error: %d", WSAGetLastError());
		}

	} while( res >= 0 );	

err:
	log(LOG_DEBUG, "closing server socket...");
	if(closesocket(server_socket)==SOCKET_ERROR) {
		log(LOG_ERR, "closesocket() failed %d", WSAGetLastError());
		return;
	}
	WSACleanup();
#else
	WSADATA wsaData;
    int iResult;

    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;

    struct addrinfo *result = NULL;
    struct addrinfo hints;

    int iSendResult;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;
    
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if ( iResult != 0 ) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return;
    }

    // Create a SOCKET for connecting to server
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return;
    }

    // Setup the TCP listening socket
    iResult = bind( ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return;
    }

    freeaddrinfo(result);

    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return;
    }

    // Accept a client socket
    ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET) {
        printf("accept failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return;
    }

    // No longer need server socket
    closesocket(ListenSocket);

    // Receive until the peer shuts down the connection
    do {

        iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
        if (iResult > 0) {
            printf("Bytes received: %d\n", iResult);

        // Echo the buffer back to the sender
            log(LOG_DEBUG, "sending recved: %s", recvbuf);
            iSendResult = send( ClientSocket, recvbuf, iResult, 0 );
            if (iSendResult == SOCKET_ERROR) {
                printf("send failed with error: %d\n", WSAGetLastError());
                closesocket(ClientSocket);
                WSACleanup();
                return;
            }
            printf("Bytes sent: %d\n", iSendResult);
        }
        else if (iResult == 0)
            printf("Connection closing...\n");
        else  {
            printf("recv failed with error: %d\n", WSAGetLastError());
            closesocket(ClientSocket);
            WSACleanup();
            return;
        }

    } while (iResult > 0);

    // shutdown the connection since we're done
    iResult = shutdown(ClientSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ClientSocket);
        WSACleanup();
        return;
    }

    // cleanup
    closesocket(ClientSocket);
    WSACleanup();

    return;
#endif
}

void find_opponet()
{
#if 0
	SOCKET client_socket = INVALID_SOCKET;
	struct sockaddr_in service;
	WSADATA wsaData;

	log(LOG_DEBUG, "find_opponet starting");

	// https://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-wsastartup
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR) {
		log(LOG_ERR, "WSAStartup() failed");
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

	// https://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-connect
	log(LOG_DEBUG, "connecting...");
	if (connect(client_socket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
		log(LOG_ERR, "connect() failed %d", WSAGetLastError());
		goto err_client;
	}

	char lol[512] = "hiiamserverfiuiquifhqeihfiuqhuihi1h2uieh1i2he1iu";
	int sent;
	log(LOG_DEBUG, "sending...");
    if((sent=send(client_socket, lol, (int)strlen(lol), 0)) == SOCKET_ERROR) {
		log(LOG_ERR, "send() failed %d", WSAGetLastError());
		goto err_client;
    }
	log(LOG_DEBUG, "sent %d", sent);

	Sleep(2000);
	log(LOG_DEBUG, "shutdown...");
    if(shutdown(client_socket, SD_BOTH) == SOCKET_ERROR) {
		log(LOG_ERR, "shutdown() failed %d", WSAGetLastError());
		goto err_client;
    }	

err_client:
	log(LOG_DEBUG, "closing client socket...");
	if(closesocket(client_socket) == SOCKET_ERROR) {
		log(LOG_ERR, "closesocket() failed %d", WSAGetLastError());
		return;
	}
	WSACleanup();
#else
	WSADATA wsaData;
    SOCKET ConnectSocket = INVALID_SOCKET;
    struct addrinfo *result = NULL,
                    *ptr = NULL,
                    hints;
    const char *sendbuf = "this is a test";
    char recvbuf[DEFAULT_BUFLEN];
    int iResult;
    int recvbuflen = DEFAULT_BUFLEN;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return;
    }

    ZeroMemory( &hints, sizeof(hints) );
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    iResult = getaddrinfo("127.0.0.1", DEFAULT_PORT, &hints, &result);
    if ( iResult != 0 ) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return;
    }

    // Attempt to connect to an address until one succeeds
    for(ptr=result; ptr != NULL ;ptr=ptr->ai_next) {

        // Create a SOCKET for connecting to server
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, 
            ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            return;
        }

        // Connect to server.
        iResult = connect( ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        WSACleanup();
        return;
    }

    // Send an initial buffer
	log(LOG_DEBUG, "sending: %s", sendbuf);
	iResult = send( ConnectSocket, sendbuf, (int)strlen(sendbuf), 0 );
    if (iResult == SOCKET_ERROR) {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return;
    }

    printf("Bytes Sent: %ld\n", iResult);

    // shutdown the connection since no more data will be sent
    iResult = shutdown(ConnectSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return;
    }

    // Receive until the peer closes the connection
    do {

        iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
        if ( iResult > 0 ){
            printf("Bytes received: %d\n", iResult);
            log(LOG_DEBUG, "str received: %s", recvbuf);
		}else if ( iResult == 0 )
            printf("Connection closed\n");
        else
            printf("recv failed with error: %d\n", WSAGetLastError());

    } while( iResult > 0 );

    // cleanup
    closesocket(ConnectSocket);
    WSACleanup();

    return;
#endif
}
#endif // 0
