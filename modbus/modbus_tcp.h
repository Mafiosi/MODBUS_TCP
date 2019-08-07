//
// Created by Joao Beleza on 15-Oct-18.
//

#ifndef modbus_tcp_h
#define modbus_tcp_h

#include "general.h"
#include "socket.h"

//RETURNS SERVER APDU
uint8_t rcv_apdu(int socket, uint16_t* transaction_id, uint8_t** apdu, uint16_t* apdu_size);

#endif //modbus_tcp_h
