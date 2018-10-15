//
// Created by Joao Beleza on 15-Oct-18.
//

#ifndef modbus_ap_h
#define modbus_ap_h

//LIBRARIES
#include "general.h"
#include "socket.h"
#include "device_driver.h"

//STRUCT FOR PASSING DATA TO THREAD
typedef struct data_thread {
    int new_socket;
    device* driver;
} data;

//INCLUDED FUNCTIONS
    //SERVER
int server_init(char* ip, int port);
void server_start(int server, device* driver);

    //SERVER PROCESSING
void server_process_client(int client, device* driver);


#endif //MODBUS_AP_H
