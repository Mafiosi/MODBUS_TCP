//
// Created by Joao Beleza on 15-Oct-18.
//

#include "device_driver.h"

//INTERACT WITH DEVICE
    //GET NEW DEVICE
device* device_new(){

    device* new_device = (device*)calloc(1, sizeof(device));
    new_device -> size = DEVICE_SIZE;
    return new_device;
}

void device_free(device* driver){
    free(driver);
}

//READ DEVICE VARIABLES
uint16_t device_get_size(device* driver){
    return driver->size;
}

uint16_t device_read_reg(device* driver, uint16_t pos){
    return driver->regs[pos];
}

uint8_t device_read_coil(device* driver, uint16_t pos){
    return driver->coils[pos];
}

//WRITE DEVICE VARIABLES
void device_write_reg(device* driver, uint16_t pos, uint16_t value){
    driver->regs[pos] = value;
}

void device_write_coil(device* driver, uint16_t pos, uint8_t value){
    driver->coils[pos] = value;
}