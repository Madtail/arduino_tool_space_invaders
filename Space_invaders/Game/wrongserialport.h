#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <windows.h>
#include <iostream>
#include <string>

#define BUFSIZE 1024

// Open serial port

/*
typedef struct
{
	char buffer[BUFSIZE];
}Databuffer;

*/


HANDLE openSerialPort();
std::string readFromPort(HANDLE port);
std::string writeToPort(HANDLE port);

#endif // SERIALPORT_H