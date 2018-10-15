//
// Created by Joao Beleza on 15-Oct-18.
//

#include "device_driver.h"

device* device_new(){

    device* new_device = (device*)calloc(1, sizeof(device));
    new_device -> size = DEVICE_SIZE;
    return new_device;
}