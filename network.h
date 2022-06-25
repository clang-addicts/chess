#ifndef __NETWORK_H__
#define __NETWORK_H__

#define WIN32_LEAN_AND_MEAN // TODO: check delete
#define DEFAULT_IP "127.0.0.1"
#define DEFAULT_PORT "9999"
#define DEFAULT_BUFLEN 512 // TODO: delete

// need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#include "log.h"
#include <stdio.h>
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <stdlib.h>

/* TODO: work
struct server_info {
    
};
struct client_info {
    
};
*/

void wait_for_opponet(void);
void* network_find_opponet(void);
void find_opponet(void);

#endif // __NETWORK_H__