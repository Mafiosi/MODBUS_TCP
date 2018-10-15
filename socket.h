//
// Created by Joao Beleza on 15-Oct-18.
//

#ifndef socket_h
#define socket_h

#include "general.h"

//SOCKET FUNCTION
struct sockaddr_in socket_addr(char* ip, int port);

//SOCKET CHECK READ SIZE IS CORRECT
uint8_t socket_read(int socket, uint8_t* buffer, int size);


#endif //TP2_SOCKET_H
