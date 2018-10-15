//
// Created by Joao Beleza on 15-Oct-18.
//

#include "general.h"
#include "modbus_ap.h"
#include "device_driver.h"

int main(int argc, char* argv[]) {

    //FUNCTION FROM MODBUS_AP
    int server = server_init(SERVERIP_DEF, PORT_DEF);

    //FUNCTION FROM DEVICE DRIVER
    device* driver = device_new();

    server_start(server, driver);






}