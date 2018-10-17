//
// Created by Joao Beleza on 15-Oct-18.
//

#include "general.h"
#include "modbus_ap.h"
#include "socket.h"

//WRITE_MULTIPLE_REGS
void write_multiple_regs(int socket){

    //GIVE RANDOM VALUES TO SUBMIT
    int msg_size = ((rand() %  (10)) + 1);
    int msg_pos  = ((rand() % (101)) + 0);

    printf("Writing %d registers at position %d\n", msg_size, msg_pos);

    uint16_t* values = ((uint16_t*)calloc((msg_size), sizeof(uint16_t)));
    for(int i = 0; i < msg_size; i++){
        values[i] = (uint16_t)((rand() % (991)) + 10);
    }

    //FUNCTION IN MODBUS_AP
    error_t result = client_write_multiple_regs(socket, msg_pos, msg_size, values);

    if (result){
        printf("ERROR: In Write Multiple Registers Client, %d\n", result);
    }
    else{
        printf("It was a Success\n");
        for (int i = 0; i < msg_size; i++){
            printf("%hu", values[i]);
        }
        printf("\n");
    }
    free(values);
}

//READ MULTIPLE REGS
void read_multiple_regs(int socket){

    //GIVE RANDOM VALUES TO SUBMIT
    int msg_size = ((rand() %  (10)) + 1);
    int msg_pos  = ((rand() % (101)) + 0);

    printf("Read %d registers at position %d\n", msg_size, msg_pos);

    //FUNCTION IN MODBUS_AP
    uint16_t* values;
    uint16_t  nothing;
    error_t result = client_read_multiple_regs(socket, msg_pos,msg_size, &values, &nothing);

    if(result){
        printf("ERROR: In Read Multiple Registers Client, %d\n", result);
    }
    else{
        printf("It was a Sucess\n");
        for(int i = 0; i < msg_size; i++){
            printf(" %hu", values[i]);
        }
        printf("\n");
    }
    free(values);
}

//WRITE_MULTIPLE_COILS
void write_multiple_coils(int socket){

    //GIVE RANDOM VALUES TO SUBMIT
    int msg_size = ((rand() %  (10)) + 1);
    int msg_pos  = ((rand() % (101)) + 0);

    printf("Writing %d coils at position %d\n", msg_size, msg_pos);

    uint8_t* values = ((uint8_t*)calloc((msg_size), sizeof(uint16_t)));
    for(int i = 0; i < msg_size; i++){
        values[i] = (uint8_t)((rand() % (2)) + 0);
    }

    //FUNCTION IN MODBUS_AP
    error_t result = client_write_multiple_coils(socket, msg_pos, msg_size, values);

    if (result){
        printf("ERROR: In Write Multiple Coils Client, %d\n", result);
    }
    else{
        printf("It was a Success\n");
        for (int i = 0; i < msg_size; i++){
            printf("%hu", values[i]);
        }
        printf("\n");
    }
    free(values);
}

//READ MULTIPLE REGS
void read_multiple_coils(int socket){

    //GIVE RANDOM VALUES TO SUBMIT
    int msg_size = ((rand() %  (10)) + 1);
    int msg_pos  = ((rand() %  (11)) + 0);

    printf("Read %d Coils at position %d\n", msg_size, msg_pos);

    //FUNCTION IN MODBUS_AP
    uint16_t* values;
    uint16_t  nothing;
    error_t result = client_read_multiple_regs(socket, msg_pos,msg_size, &values, &nothing);

    if(result){
        printf("ERROR: In Read Multiple Registers Client, %d\n", result);
    }
    else{
        printf("It was a Sucess\n");
        for(int i = 0; i < msg_size; i++){
            printf(" %hu", values[i]);
        }
        printf("\n");
    }
    free(values);
}

//MAIN CLIENT FUNCTION
int main(int argc, char* argv[]){

    //FUNCTION IN MODBUS_AP
    int socket = client_connect(SERVERIP_DEF, PORT_DEF);
    printf("Connected to Server\n");

    char* str[255] = {0};
    int ans;

    printf("ENTER ONE OF THE FOLLOWING OPTIONS\n");
    printf("--> 1 <-- WRITE MULTIPLE REGS\n");
    printf("--> 2 <-- READ  MULTIPLE REGS\n");
    printf("--> 3 <-- WRITE MULTIPLE COILS\n");
    printf("--> 4 <-- READ  MULTIPLE COILS\n");
    printf("--> 5 <-- EXIT\n");

    while (ans != 5) {

        scanf("%s", str[0]);
        if (ans = (str[0] - '0')) {

            //FUNCTIONS INSIDE CLIENT
            switch (ans) {
                case 1:
                    write_multiple_regs(socket);
                    break;
                case 2:
                    read_multiple_regs(socket);
                    break;
                case 3:
                    write_multiple_coils(socket);
                    break;
                case 4:
                    read_multiple_coils(socket);
                    break;
                case 5:
                    printf("Exiting Client;");
                    break;
                default:
                    printf("Undefined Value\n");
            }

            sleep(1);
        }

        else {
            printf("INVALID INPUT, TRY AGAIN \n");
        }
    }

    //FUNCTION INSIDE SOCKET
    socket_close(socket);
    printf("Disconnected from Server");
    return 0;
}