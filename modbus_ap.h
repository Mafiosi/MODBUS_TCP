//
// Created by Joao Beleza on 15-Oct-18.
//

#ifndef modbus_ap_h
#define modbus_ap_h

//LIBRARIES
#include "general.h"
#include "socket.h"
#include "device_driver.h"
#include "modbus_tcp.h"

//STRUCT FOR PASSING DATA TO THREAD
/*typedef struct data_thread {
    int new_socket;
    device* driver;
} data;*/

//CODE FOR READING FUNCTIONS
typedef enum {
    READ_COILS  = 0x01,
    READ_REGS   = 0x03,
    WRITE_COILS = 0x0F,
    WRITE_REGS  = 0x10
} function_code_t;


//INCLUDED FUNCTIONS
    //SERVER
int server_init(char* ip, int port);
int server_start(int server, device* driver);

    //SERVER PROCESSING
int server_process_client(int client, device* driver);
void server_process_request(uint8_t* req_apdu, uint16_t req_apdu_size, device* driver, uint8_t** resp_apdu, uint16_t* resp_apdu_size);



#endif //MODBUS_AP_H
