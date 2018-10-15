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

void server_start(int server, device* driver){
    printf("Server has started\n");

    int client_socket, *new_socket;
    struct sockaddr_in cli_addr;
    socklen_t client_addr_len = sizeof(cli_addr);

    while(1) {

        client_socket = accept(server, (struct sockaddr *) &cli_addr, &client_addr_len);

        //ERROR WARNING
        if (client_socket == -1) {
            printf("ERROR: Accepting Connetion");
            break;
        }

        printf("Connection Accepted\n");

        pthread_t sniffer_thread;
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
    }


}


//SERVER PROCESSING FUNCTIONS
void server_process_client(void* data_thread){

    struct data_thread *data = malloc(sizeof(struct data_thread));




}