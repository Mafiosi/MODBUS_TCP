//
// Created by Joao Beleza on 15-Oct-18.
//

#include "modbus_tcp.h"

uint8_t rcv_apdu(int socket, uint16_t* transaction_id, uint8_t** apdu, uint16_t* apdu_size){

    uint8_t mbap[7];

    //FUNCTION INSIDE SOCKET
    if(!socket_read(socket, mbap, 7)){
        return 0;
    }

    //mbap[0] - b8_high || mbap[1] - b8_low |! transaction_id - mbap[0] and [1]
    *transaction_id = (((mbap[0]) << 8) | (mbap[1]));

    //mbap[4] - b8_high || mbap[5] - b8_low |! apdu_size - mbap[4] and [5]
    *apdu_size = (((mbap[4]) << 8) | (mbap[5]));

    //resize apdu to allocate size
    (*apdu_size)--;

    //SEND APDU TO SOCKET
    *apdu = ((uint8_t*)calloc((*apdu_size), sizeof(uint8_t)));
    //FUNCTION INSIDE SOCKET
    return socket_read(socket, *apdu, *apdu_size);
}