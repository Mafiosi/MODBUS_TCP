//
// Created by Joao Beleza on 15-Oct-18.
//

#include "socket.h"

//RETURN A FULLY IMPLEMENTED SOCKET
struct sockaddr_in socket_addr(char* ip, int port) {

    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;
    return addr;
}

//CHECKS THAT SIZE IS CORRECT
uint8_t socket_read(int socket, uint8_t* buffer, int size){
    long bytes_read;

    for(long pos = 0; pos < size; pos = pos + bytes_read){

        bytes_read = read(socket, buffer + pos, size - pos);

        if (bytes_read <= 0){
            return 0;
        }
    }

    return 1;
}