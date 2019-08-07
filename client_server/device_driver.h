//
// Created by Joao Beleza on 15-Oct-18.
//

#ifndef device_driver_h
#define device_driver_h

#include "general.h"

//STRUCT FOR DEVICE NEEDED
typedef struct _device {
    uint16_t regs[DEVICE_SIZE];
    uint8_t  coils[DEVICE_SIZE];
    uint16_t size;
} device;

//INTERACT WITH DEVICE
device* device_new();
void device_free(device* driver);

//READ DRIVER VARIABLES
uint16_t device_get_size(device* driver);
uint16_t device_read_reg(device* driver, uint16_t pos);
uint8_t device_read_coil(device* driver, uint16_t pos);

//WRITE DRIVER VARIABLES
void device_write_reg(device* driver, uint16_t pos, uint16_t value);
void device_write_coil(device* driver, uint16_t pos, uint8_t value);


#endif //TP2_DEVICE_DRIVER_H
