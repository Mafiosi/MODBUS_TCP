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

device* device_new();

#endif //TP2_DEVICE_DRIVER_H
