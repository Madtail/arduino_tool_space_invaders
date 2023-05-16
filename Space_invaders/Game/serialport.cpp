#include "serialport.h"

void openSerialPort()
{
	serialHandle = CreateFile("\\\\.\\COM3", GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	// Do some basic settings
	DCB serialParams = { 0 };
	serialParams.DCBlength = sizeof(serialParams);


	GetCommState(serialHandle, &serialParams);
	serialParams.BaudRate = 9600;
	serialParams.ByteSize = 8;
	serialParams.StopBits = TWOSTOPBITS;
	serialParams.Parity = NOPARITY;
	SetCommState(serialHandle, &serialParams);

	// Set timeouts
	COMMTIMEOUTS timeout = { 0 };
	timeout.ReadIntervalTimeout = 50;
	timeout.ReadTotalTimeoutConstant = 50;
	timeout.ReadTotalTimeoutMultiplier = 50;
	timeout.WriteTotalTimeoutConstant = 50;
	timeout.WriteTotalTimeoutMultiplier = 10;

	SetCommTimeouts(serialHandle, &timeout);
}

typedef struct
{
	char buffer[BUFSIZE];
}Databuffer;

Databuffer readFromPort(HANDLE port, DWORD bytesRead)
{
	bytesRead = 0;
	Databuffer buffer{};
	if (ReadFile(port, &buffer, BUFSIZE, &bytesRead, NULL)) {
		return buffer;
	}
}

Databuffer writeToPort(HANDLE port, DWORD bytesWritten)
{
	bytesWritten = 0;
	Databuffer buffer{};
	if (ReadFile(port, &buffer, BUFSIZE, &bytesWritten, NULL)) {
		std::cout << "Successfully written!\n" << std::endl;
	}
}