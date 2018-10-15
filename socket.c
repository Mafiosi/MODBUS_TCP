//
// Created by Joao Beleza on 15-Oct-18.
//

#include "socket.h"

struct sockaddr_in socket_addr(char* ip, int port) {

    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;
    return addr;
}