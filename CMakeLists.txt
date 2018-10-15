cmake_minimum_required(VERSION 3.12)
project(TP2 C)

set(CMAKE_C_STANDARD 99)

add_executable(TP2 server.c server.h client.c client.h modbus_ap.c modbus_ap.h general.h socket.c socket.h device_driver.c device_driver.h)