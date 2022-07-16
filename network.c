#include "network.h"

char buffer[4096] = "Hello, World!";
#define PORT 9000

void* network_find_opponet() {
    printf("find net opponet!\n");   
    return NULL;
}

void wait_for_opponet()
{
	WSADATA wsaData;
    struct addrinfo addr_hint;
    struct addrinfo *addr_result    = NULL;
    SOCKET server_socket            = INVALID_SOCKET;
    SOCKET client_socket            = INVALID_SOCKET;
    int res                         = 0;
    char buf[DEFAULT_BUFLEN]        = {0};

    // https://docs.microsoft.com/en-us/previous-versions/windows/desktop/legacy/aa366920(v=vs.85)
    ZeroMemory(&addr_hint, sizeof(addr_hint));
    
    // initialize winsock
    // https://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-wsastartup
    res = WSAStartup(MAKEWORD(2,2), &wsaData);
    if(res != 0) {
        logd(LOG_ERR, "failed with error: %d", res);
        return;
    }

    addr_hint.ai_family     = AF_INET;
    addr_hint.ai_socktype   = SOCK_STREAM;
    addr_hint.ai_protocol   = IPPROTO_TCP;
    addr_hint.ai_flags      = AI_PASSIVE;

    // resolve address and port
    // https://docs.microsoft.com/en-us/windows/win32/api/ws2tcpip/nf-ws2tcpip-getaddrinfo
    res = getaddrinfo(NULL, DEFAULT_PORT, &addr_hint, &addr_result);
    if(res != 0) {
        logd(LOG_ERR, "failed with error: %d", res);
        goto error_server;
    }

    // create a SOCKET for connecting to server
    // https://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-socket
    server_socket = socket(addr_result->ai_family, addr_result->ai_socktype, addr_result->ai_protocol);
    if(server_socket == INVALID_SOCKET) {
        logd(LOG_ERR, "failed with error: %ld", WSAGetLastError());
        goto error_server;
    }

    // setup the TCP listening socket
	// https://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-bind
    res = bind(server_socket, addr_result->ai_addr, (int)addr_result->ai_addrlen);
    if(res == SOCKET_ERROR) {
        logd(LOG_ERR, "failed with error: %ld", WSAGetLastError());
        goto error_server;
    }

    // start listening to TCP socket
	// https://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-listen
    res = listen(server_socket, SOMAXCONN);
    log(LOG_INFO, "[server] now listening for player");
    if (res == SOCKET_ERROR) {
        logd(LOG_ERR, "failed with error: %ld", WSAGetLastError());
        goto error_server;
    }

    // accept a client socket
	// https://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-accept
    client_socket = accept(server_socket, NULL, NULL);
    if(client_socket == INVALID_SOCKET) {
        logd(LOG_ERR, "failed with error: %ld", WSAGetLastError());
        goto error_server;
    }

    // receive until the peer shuts down the connection
    do {
        // wait until client sends data
        // https://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-recv
        res = recv(client_socket, buf, sizeof(buf), 0);
        if(res > 0) {
            logd(LOG_DEBUG, "[Server] received: %d bytes", res);
            logd(LOG_DEBUG, "[Server] received string: %s", buf);

            snprintf(buf, DEFAULT_BUFLEN, "Hello Client! I'm the SERVER!");
            logd(LOG_DEBUG, "[Server] sending: %d bytes", strlen(buf));
            logd(LOG_DEBUG, "[Server] sending string: %s", buf);

            // sending new data to client
            // https://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-send
            res = send(client_socket, buf, strlen(buf), 0); //?????? maybe size has to do with long wait buffering? this param might be the cause
            if (res == SOCKET_ERROR) {
                logd(LOG_ERR, "failed with error: %ld", WSAGetLastError());
                goto error_server;
            }

            logd(LOG_DEBUG, "[Server] received: %d bytes", res);
        } else if (res == 0) {
            logd(LOG_DEBUG, "[Server] closing connection");
        } else {
            logd(LOG_ERR, "failed with error: %ld", WSAGetLastError());
            goto error_server;
        }

    } while(res > 0);

    // shutdown the connection 
    res = shutdown(client_socket, SD_SEND);
    if(res == SOCKET_ERROR) {
        logd(LOG_ERR, "failed with error: %ld", WSAGetLastError());
        goto error_server;
    }

error_server:
    // clean up
    if(addr_result) {
        freeaddrinfo(addr_result);
    }
    if(server_socket) {
        closesocket(server_socket);
    }
    if(client_socket) {
        closesocket(client_socket);
    }
    WSACleanup();
    return;
}

void find_opponet()
{
    SOCKET ConnectSocket = INVALID_SOCKET;
    struct addrinfo *result = NULL,
                    *ptr = NULL,
                    hints;
    const char *sendbuf = "this is a test";
    char recvbuf[DEFAULT_BUFLEN];
    int iResult;
    int recvbuflen = DEFAULT_BUFLEN;

    ////////////////////////////////////////

	WSADATA wsaData;
    SOCKET client_socket            = INVALID_SOCKET;
    struct addrinfo addr_hint;
    struct addrinfo *addr_result    = NULL;
    int res                         = 0;
    char buf[DEFAULT_BUFLEN]        = {0};

    // https://docs.microsoft.com/en-us/previous-versions/windows/desktop/legacy/aa366920(v=vs.85)
    ZeroMemory(&addr_hint, sizeof(addr_hint));

    // initialize winsock
    // https://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-wsastartup
    res = WSAStartup(MAKEWORD(2,2), &wsaData);
    if(res != 0) {
        logd(LOG_ERR, "failed with error: %d", res);
        return;
    }

    addr_hint.ai_family     = AF_UNSPEC;
    addr_hint.ai_socktype   = SOCK_STREAM;
    addr_hint.ai_protocol   = IPPROTO_TCP;

    // resolve address and port
    // https://docs.microsoft.com/en-us/windows/win32/api/ws2tcpip/nf-ws2tcpip-getaddrinfo
    res = getaddrinfo(DEFAULT_IP, DEFAULT_PORT, &addr_hint, &addr_result);
    if(res != 0) {
        logd(LOG_ERR, "failed with error: %d", res);
        goto error_client;
    }

    // TODO: study // attempt to connect to an address until one succeeds
    for(ptr=addr_result; ptr != NULL ;ptr=ptr->ai_next) {
        // create a socket to connect to server
        client_socket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if(client_socket == INVALID_SOCKET) {
            logd(LOG_ERR, "failed with error: %ld", WSAGetLastError());
            goto error_client;
        }

        // connect to server
        res = connect(client_socket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if(res == SOCKET_ERROR) {
            closesocket(client_socket);
            client_socket = INVALID_SOCKET;
            continue;
        }

        // stop if no error on connect()
        break;
    }

    if(client_socket == INVALID_SOCKET) {
        logd(LOG_ERR, "unable to connect, exiting");
        goto error_client;
    }

    snprintf(buf, DEFAULT_BUFLEN, "Hi, I'm the CLIENT. Nice to meet you!");

    // send an initial buffer
	logd(LOG_DEBUG, "[Client] sending: %d", strlen(buf));
	logd(LOG_DEBUG, "[Client] sending string: %s", buf);
	res = send(client_socket, buf, strlen(buf), 0);
    if(res == SOCKET_ERROR) {
        logd(LOG_ERR, "send failed with error: %d", WSAGetLastError());
        goto error_client;
    }
	logd(LOG_DEBUG, "[Client] sent: %d", res);

    // shutdown the connection since no more data will be sent
    res = shutdown(client_socket, SD_SEND);
    if(res == SOCKET_ERROR) {
        logd(LOG_ERR, "shutdown failed with error: %d", WSAGetLastError());
        goto error_client;
    }

    // receive until the peer closes the connection
    do {
        ZeroMemory(buf, DEFAULT_BUFLEN);
        res = recv(client_socket, buf, strlen(buf), 0);
        if(res > 0) {
            logd(LOG_DEBUG, "[Client] recieved: %d", res);
            logd(LOG_DEBUG, "[Client] recieved string: %s", buf);
        } else if (res == 0) {
            logd(LOG_DEBUG, "[Client] connection closed");
        } else {
            logd(LOG_ERR, "[Client] recv() failed with error: %d", WSAGetLastError());
        }
    } while(res > 0);

error_client:
    // cleanup
    if(addr_result) {
        freeaddrinfo(addr_result);
    }
    if(client_socket) {
        closesocket(client_socket);
    }
    WSACleanup();

    return;
}