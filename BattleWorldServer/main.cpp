#include <iostream>
#include <Python.h>
#include <SDL.h>
#include <boost/asio.hpp>
#include <vector>

struct player {
	int ID;
	int status;
	int x;
	int y;
	int vx;
	int vy;
};

typedef struct player playerSt;

bool sendingOutputBuffer = false;
int Unused_ID = 0;
char buffoutfront[64] = { '\0' };
char buffoutback[64] = { '\0' };
char* frontBuffptr;
char* backBuffptr;
char* swapTemp;
std::vector<playerSt> playerStack;


int stringSaver(void* data) {
	while (true) {
		strcpy(backBuffptr, "hello");
		if (!sendingOutputBuffer) {
			swapTemp = backBuffptr;
			backBuffptr = frontBuffptr;
			frontBuffptr = backBuffptr;
		}
	}
	return 0;
}

int main(int argc, char* argv[]) {
	using boost::asio::ip::udp;
	boost::asio::io_service io_service;
	udp::socket socket(io_service, udp::endpoint(udp::v4(), 12002));
	udp::endpoint sender;
	char buffin[64] = { '\0' };
	int bufferlength;
	char buff[100];
	SDL_Thread* thrptr = SDL_CreateThread(stringSaver, "outputStringSaverThread", (void *)(buff));
	playerSt loopPlObject;
	while (true){
		bufferlength = socket.available();
		if (bufferlength) {
			socket.receive_from(boost::asio::buffer(buffin, sizeof(buffin)), sender);
			buffin[bufferlength] = { '\0' };
			std::cout << buffin << std::endl;
			sender.port(12006);
			std::cout << sender.address().to_string() << "    " << bufferlength << "   " << (int)buffin << "   " << std::endl;
			if (buffin[0] == 'N') {
				socket.send_to(boost::asio::buffer(std::to_string(Unused_ID)), sender);
				Unused_ID += 1;
			}
			else {
				sendingOutputBuffer = true;
				socket.send_to(boost::asio::buffer(std::string(frontBuffptr)), sender);
				sendingOutputBuffer = false;
			}
		}
		SDL_Delay(10);
	}


	
	getchar();
	
	return 0;
}
//Py_Initialize();
/*const char* svpy = "from socket import *\n\
serverPort = 12002\n\
serverSocket = socket(AF_INET, SOCK_DGRAM)\n\
serverSocket.bind(('', serverPort))\n\
while 1:\n\
message, clientAddress = serverSocket.recvfrom(2048)\n\
print clientAddress\n\
print message";*/
//PyRun_SimpleString(svpy);
//Py_Finalize();