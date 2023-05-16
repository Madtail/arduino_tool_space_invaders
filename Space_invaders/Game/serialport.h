#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <Windows.h>
#include "game.h"

// Open serial port
HANDLE serialHandle;
char  chBuffer[BUFSIZE]{};
DWORD dwBytesRead = 0;
DWORD dwBytesWritten = 0;
void openSerialPort();

#endif // SERIALPORT_H