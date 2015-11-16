#include <iostream>
#include <SDL.h>
#include <sstream>
#include <boost/asio.hpp>

/*struct player {
	int ID;
	int status;
	int x;
	int y;
	int vx;
	int vy;
};*/

struct data {
	int ID;
	int status;
	char data_string[15];
};
bool switchingBuffers = false;
bool replacingMasterString = false;
bool replacingString = false;
bool sendingOutputBuffer = false;
int Unused_ID = 0;
char buffoutfront[1024] = { '\0' };
char buffoutback[1024] = { '\0' };
char* frontBuffptr = buffoutfront;
char* backBuffptr = buffoutback;
char* swapTemp;
std::string backBufferString;
struct data dataStack[100];

int stringSaver(void* data) {
	while (true) {
		/*while (replacingString) {
		}
		*/

		//std::cout << "String saver : " << dataStack[0].data_string << std::endl;

		backBufferString = "DATA";
		for (int i = 0; i < Unused_ID; i++) {

			if (!dataStack[i].status) {
				backBufferString += "\n";
				backBufferString += dataStack[i].data_string;
			}
		}
		while (replacingString) {
		}
		replacingMasterString = true;
		strcpy(backBuffptr, backBufferString.c_str());
		replacingMasterString = false;
		
		if (!sendingOutputBuffer) {
			switchingBuffers = true;
			swapTemp = backBuffptr;
			backBuffptr = frontBuffptr;
			frontBuffptr = swapTemp;
			switchingBuffers = false;
		}
	}
	return 0;
}

int main(int argc, char* argv[]) {
	using boost::asio::ip::udp;

	boost::asio::io_service io_service;
	udp::socket socket(io_service, udp::endpoint(udp::v4(), 12002));
	udp::endpoint sender;
	
	char buffin[1024] = { '\0' };
	int bufferlength;
	int loopIntID;
	//std::stringstream ss;
	std::string loopString;

	char data[100];
	SDL_Thread* thrptr = SDL_CreateThread(stringSaver, "outputStringSaverThread", (void *)(data));
	/*loopPlObject.ID = 0;
	loopPlObject.status = 1;
	loopPlObject.vx = 1;
	loopPlObject.vy = 1;
	loopPlObject.x = 1;
	loopPlObject.y = 1;
	playerStack.push_back(loopPlObject);
	std::cout << (playerStack.at(0)).ID << std::endl;
	loopPlObject.ID = 1;
	std::cout << (playerStack.at(0)).ID << std::endl;
	getchar();*/
	while (true){
		bufferlength = socket.available();
		if (bufferlength) {
			//std::cout << "Buffer Length : " << bufferlength << "\n";
			//getchar();
			socket.receive_from(boost::asio::buffer(buffin, sizeof(buffin)), sender);
			buffin[bufferlength] = { '\0' };
			sender.port(12006);
			std::cout << "buffin: " << buffin << std::endl;
			//std::cout << sender.address().to_string() << "    " << bufferlength << "   " << (int)buffin << "   " << std::endl;
			if (bufferlength == 1) {
				socket.send_to(boost::asio::buffer(std::to_string(Unused_ID)), sender);
				dataStack[Unused_ID].ID = Unused_ID;
				dataStack[Unused_ID].status = 0;
				strcpy(dataStack[Unused_ID].data_string,(std::to_string(Unused_ID) + " 0 0 0 0").c_str());
				Unused_ID += 1;
			}
			else {
				sscanf(buffin, "%d", &loopIntID);
				if(!replacingMasterString) {
					replacingString = true;
					strcpy(dataStack[loopIntID].data_string, buffin);
					//std::cout << "I Came : " << buffin << "    " << dataStack[loopIntID].data_string << "      " << loopIntID << std::endl;
					replacingString = false;
				}
				//sscanf(buffin,"%d %d %d %d %d",&loopIntID,&loopX,&loopY,&loopVx,&loopVy);
				/*playerStack[loopIntID].x = loopX;
				playerStack[loopIntID].y = loopY;
				playerStack[loopIntID].vx = loopVx;
				playerStack[loopIntID].vy = loopVy;
				*/
				//std::cout << loopIntID << std::endl;
				//std::cout << loopIntID << (playerStack[0]).x << (playerStack[0]).y << (playerStack[0]).vx << (playerStack[0]).vy << std::endl;
				while (switchingBuffers) {
				}
				sendingOutputBuffer = true;
				std::cout << "Front Buffer (sending) : " << frontBuffptr << std::endl;
				socket.send_to(boost::asio::buffer(std::string(frontBuffptr)), sender);
				sendingOutputBuffer = false;
			}
		}
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