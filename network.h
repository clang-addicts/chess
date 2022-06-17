#ifndef __NETWORK_H__
#define __NETWORK_H__

#include "log.h"

#include <stdio.h>
#include <winsock2.h>
//#pragma comment(lib,"Ws2_32.lib")
//#include <ws2tcpip.h> // __imp_socket, __imp_closesock undefined error fix

void wait_for_opponet(void);
void* network_find_opponet(void);
void find_opponet(void);

#endif // __NETWORK_H__