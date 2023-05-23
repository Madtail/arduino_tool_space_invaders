#include "serialport.h"

bool status;

//Returns the last Win32 error, in string format. Returns an empty string if there is no error.
std::string GetLastErrorAsString()
{
	//Get the error message ID, if any.
	DWORD errorMessageID = ::GetLastError();
	if (errorMessageID == 0) {
		return std::string(); //No error message has been recorded
	}

	LPSTR messageBuffer = nullptr;

	//Ask Win32 to give us the string version of that message ID.
	//The parameters we pass in, tell Win32 to create the buffer that holds the message for us (because we don't yet know how long the message string will be).
	size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

	//Copy the error message into a std::string.
	std::string message(messageBuffer, size);

	//Free the Win32's string's buffer.
	LocalFree(messageBuffer);

	return message;
}

HANDLE openSerialPort()
{
	HANDLE serialHandle;
	
	serialHandle = CreateFile("\\\\.\\COM3", GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	std::cout << "Opened serial port" << std::endl;

	if (serialHandle == INVALID_HANDLE_VALUE) {
		std::cout << GetLastErrorAsString() << std::endl;
	}

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
	return serialHandle;
}

// TODO: Fix reading
std::string readFromPort(HANDLE port)
{
	DWORD bytesRead;
	char buffer[BUFSIZE] = { 0 };
	char readData;
	unsigned char loop = 0;

	do
	{
		status = ReadFile(port, &readData, sizeof(buffer), &bytesRead, NULL);
		if (!status) {
			std::cout << GetLastErrorAsString() << std::endl;
		}
		//std::cout << "status: " << status << std::endl;
		buffer[loop] = readData;
		//std::cout << buffer[loop] << "\n";
		++loop;
	} while (bytesRead > 0);
	--loop;
	if (buffer != nullptr)
	{
		std::string message;

		for (int i = 0; i < loop; ++i) {
			message += buffer[loop];
		}
		return message;
	}
	
	return "0";
}

std::string writeToPort(HANDLE port)
{
	DWORD bytesWritten;
	bytesWritten = 0;
	char buffer[BUFSIZE];
	if (WriteFile(port, buffer, BUFSIZE, &bytesWritten, NULL)) {
		std::cout << "Successfully written!\n" << std::endl;
		std::string message = buffer + '\0';
		return message;
	}
}

// Databuffer s[BUFSIZE] = { "eefef" };

/*if (ReadFile(port, buffer, BUFSIZE, &bytesRead, NULL)) {
		if (buffer != nullptr) {
			std::string message = buffer;
			std::cout << "returned" << std::endl;
			return message;
		}
	}*/