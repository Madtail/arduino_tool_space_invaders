#ifndef SERIAL_H
#define SERIAL_H
#include "serialib.h"
#include <iostream>

void configureSerialPort(serialib serial);
std::string getMessage(serialib serial, char buffer[15]);


#endif // SERIAL_H