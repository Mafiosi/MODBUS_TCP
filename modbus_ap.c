//
// Created by Joao Beleza on 15-Oct-18.
//

#include "modbus_ap.h"

//TODO FINISH MODBUS_AP FUNCTION FROM CLIENT

//SERVER MANAGE FUNCTIONS
int server_init(char* ip, int port){

    int server_socket = socket(PF_INET, SOCK_STREAM, 0);

    //ERROR WARNING
    if (server_socket < 0){
        printf("ERROR: Creating Socket");
        return 0;
    }


    int val = 1;
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));

    //FUNCTION FROM SOCKET.C
    struct sockaddr_in serv_addr = socket_addr(ip, port);

    int res = bind(server_socket, (struct sockaddr *) &serv_addr, sizeof(serv_addr));

    //ERROR WARNING
    if (res < 0){
        printf("ERROR: Binding Socket");
        return 0;
    }

    listen(server_socket, 5);
    return server_socket;
}

int server_start(int server, device* driver){
    printf("Server has started\n");

    int client_socket;
    struct sockaddr_in cli_addr;
    socklen_t client_addr_len = sizeof(cli_addr);

    client_socket = accept(server, (struct sockaddr *) &cli_addr, &client_addr_len);

    //ERROR WARNING
    if (client_socket == -1) {
        printf("ERROR: Accepting Connetion\n");
        return 0;
    }

    printf("Connection Accepted\n");

    //TODO GET THREAD WORKING TO ALLOW SEVERAL CLIENTS
    //NEED TO ADD STRUCT TYPE DATA TO ALLOW THREAD TO RECEIVE TWO PARAMETERS
    //"GET" THE TWO PARAMETERS INSIDE SERVER_PROCESS_CLIENT

    /*pthread_t sniffer_thread;
    new_socket = malloc(1);
    *new_socket = client_socket;

    struct data_thread *data = malloc(sizeof(struct data_thread));
    data -> new_socket = new_socket;
    data -> driver = driver;

    //ERROR WARNING
    if(pthread_create(&sniffer_thread, NULL, server_process_client, data) < 0){

        printf("Error: Creating Thread\n");
        break;
    }
    */

    //FUNCTION INSIDE MODBUS_AP
    int res = server_process_client(client_socket, driver);

    //ERROR WARNING
    if(res == 0){
        printf("ERROR: IN server_process_client\n");
        return 0;
    }

    return 1;
}

//SERVER INTERACTION FUNCTIONS

    //SERVER PROCESS A REQUEST FROM CLIENT
int server_process_client(int client_socket, device* driver){

    while(1){

        //GET APDU FROM TCP LAYER
        uint16_t transaction_id;
        uint8_t* req_apdu;
        uint16_t req_apdu_size;

        //FUNCTION INSIDE MODBUS_TCP
        uint8_t res = rcv_apdu(client_socket, &transaction_id, &req_apdu, &req_apdu_size);

        //ERROR WARNING
        if (res == 0){
            printf("ERROR: APDU could not be retrieved");
            break;
        }

        //PROCESS APDU
        uint8_t* resp_apdu;
        uint16_t resp_apdu_size;
        //FUNCTION INSIDE MODBUS_AP
        server_process_request(req_apdu, req_apdu_size, driver, &resp_apdu, &resp_apdu_size);
    }

}

    //SERVER PROCESS FUNCTION
void server_process_request(uint8_t* req_apdu, uint16_t req_apdu_size, device* driver, uint8_t** resp_apdu, uint16_t* resp_apdu_size){

    uint8_t function_code = req_apdu[0];
    switch(function_code) {

        //FUNCTIONS INSIDE MODBUS_AP
        case READ_REGS:
            server_process_read_multiple_regs(req_apdu, req_apdu_size, driver, resp_apdu, resp_apdu_size);
            break;

        case WRITE_REGS:
            server_process_write_multiple_regs(req_apdu, req_apdu_size, driver, resp_apdu, resp_apdu_size);
            break;

        case WRITE_COILS:
            server_process_read_multiple_coils(req_apdu, req_apdu_size, driver, resp_apdu, resp_apdu_size);
            break;

        case READ_COILS:
            server_process_write_multiple_coils(req_apdu, req_apdu_size, driver, resp_apdu, resp_apdu_size);
            break;

        default:
            server_create_err_apdu(function_code, ILLEGAL_FUNCTION, resp_apdu, resp_apdu_size);
            break;
    }
}

    //SERVER PROCESS REQUEST TO READ MULTIPLE REGS
void server_process_read_multiple_regs(uint8_t* req_apdu, uint16_t req_apdu_size, device* driver, uint8_t** resp_apdu, uint16_t* resp_apdu_size) {

    uint16_t start_addr;
    uint16_t reg_count;

    //req_apdu[1] - b8_high || req_apdu[2] - b8_low |! start_addr - req_apdu[1] and [2]
    start_addr = (((req_apdu[1]) << 8) | (req_apdu[2]));

    //req_apdu[3] - b8_high || req_apdu[4] - b8_low |! start_addr - req_apdu[3] and [4]
    reg_count = (((req_apdu[3]) << 8) | (req_apdu[4]));

    //FUNCTION INSIDE MODBUS_AP
    if (start_addr + reg_count > device_get_size(driver)) {
        server_create_err_apdu(READ_REGS, ILLEGAL_DATA_ADDRESS, resp_apdu, resp_apdu_size);
    }

    else if (reg_count <1 || reg_count > 125){
        server_create_err_apdu(READ_REGS, ILLEGAL_DATA_VALUE, resp_apdu, resp_apdu_size);
    }

    else {
        *resp_apdu_size = 2 + reg_count * 2;
        *resp_apdu = ((uint8_t*)calloc((*resp_apdu_size), sizeof(uint8_t)));

        (*resp_apdu)[0] = READ_REGS;
        (*resp_apdu)[1] = reg_count * 2;

        //FUNCTIONS INSIDE DEVICE DRIVER
        for(uint16_t i = 0; i < reg_count; i++){
            uint16_t value = device_read_reg(driver, start_addr + i);

            (*resp_apdu)[2 + i * 2 + 1] = (((value) << 8) | ((*resp_apdu)[2 + i * 2]));
        }
    }



}

    //SERVER PROCESS REQUEST TO READ MULTIPLE REGS



//CLIENT START FUNCTIONS
int client_connect(char* ip, int port){

    int client_socket = socket(PF_INET, SOCK_STREAM, 0);

    //ERROR WARNING
    if(client_socket < 0){
        printf("ERROR: Creating Socket");
    }

    //FUNCTION FROM SOCKET.C
    struct sockaddr_in client_addr = socket_addr(ip, port);

    int res = bind(client_socket, (struct sockaddr *) &client_addr, sizeof(client_addr))

    //ERROR WARNING
    if(res < 0){
        printf("ERROR: Binding Socket");
    }

    return client_socket;
}