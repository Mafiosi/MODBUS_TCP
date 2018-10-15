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

//CODE FOR ERROR VALUE
typedef enum {
    NO_ERROR            = 0x00,
    ILLEGAL_FUNCTION    = 0x01,
    ILLEGAL_DATA_ADDRESS= 0x02,
    ILLEGAL_DATA_VALUE  = 0x03,
    SLAVE_DEVICE_FAILURE= 0x04,
} error_t;

//SERVER
int server_init(char* ip, int port);
int server_start(int server, device* driver);

    //SERVER PROCESSING
int server_process_client(int client, device* driver);
void server_process_request(uint8_t* req_apdu, uint16_t req_apdu_size, device* driver, uint8_t** resp_apdu, uint16_t* resp_apdu_size);

    //SERVER CHOSE RESPONSE ACTION
void server_process_read_multiple_regs(uint8_t* req_apdu, uint16_t req_apdu_size, device* driver, uint8_t** resp_apdu, uint16_t* resp_apdu_size);
void server_process_write_multiple_regs(uint8_t* req_apdu, uint16_t req_apdu_size, device* driver, uint8_t** resp_apdu, uint16_t* resp_apdu_size);
void server_process_read_multiple_coils(uint8_t* req_apdu, uint16_t req_apdu_size, device* driver, uint8_t** resp_apdu, uint16_t* resp_apdu_size);
void server_process_write_multiple_coils(uint8_t* req_apdu, uint16_t req_apdu_size, device* driver, uint8_t** resp_apdu, uint16_t* resp_apdu_size);
void server_create_err_apdu(uint8_t err_code, error_t exception_code, uint8_t** resp_apdu, uint16_t* resp_apdu_size );

//CLIENT
int client_connect(char* ip, int port);

#endif //MODBUS_AP_H
