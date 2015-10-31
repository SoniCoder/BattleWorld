#include <iostream>
#include <Python.h>
#include <SDL.h>

const char* svpy = "from socket import *\n\
serverPort = 12002\n\
serverSocket = socket(AF_INET, SOCK_DGRAM)\n\
serverSocket.bind(('', serverPort))\n\
while 1:\n\
  message, clientAddress = serverSocket.recvfrom(2048)\n\
  print message";

int main(int argc, char* argv[]) {
	Py_Initialize();

	PyRun_SimpleString(svpy);
	getchar();
	Py_Finalize();
	return 0;
}