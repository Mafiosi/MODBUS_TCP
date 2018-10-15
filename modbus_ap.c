//
// Created by Joao Beleza on 15-Oct-18.
//

#include "modbus_ap.h"

//SERVER START FUNCTIONS
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

    int res = server_process_client(client_socket, driver);

    //ERROR WARNING
    if(res == 0){
        printf("ERROR: IN server_process_client\n");
        return 0;
    }

    return 1;
}


//SERVER PROCESSING FUNCTIONS
int server_process_client(int client_socket, device* driver){

    while(1){

        //GET APDU FROM TCP LAYER
        uint16_t transaction_id;
        uint8_t* req_apdu;
        uint16_t req_apdu_size;

        uint8_t res = rcv_apdu(client_socket, &transaction_id, &req_apdu, &req_apdu_size);

        //ERROR WARNING
        if (res == 0){
            printf("ERROR: APDU could not be retrieved");
            break;
        }

        //PROCESS APDU
        uint8_t* resp_apdu;
        uint16_t resp_apdu_size;
        server_process_request(req_apdu, req_apdu_size, driver &resp_apdu, &resp_apdu_size);


    }

}

void server_process_request(uint8_t* req_apdu, uint16_t req_apdu_size, device* driver, uint8_t** resp_apdu, uint16_t* resp_apdu_size){

    uint8_t function_code = req_apdu[0];
    switch(function_code) {

        case READ_REGS:
            server_process_read








    }


}