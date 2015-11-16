#include "Engine.h"
#include "Player.h"
#include "bw_structs.h"

//all the ingame data is shared here among functions
mainData dataUnit;
char* finder;
char* found;
bool tmpbool;
struct player tmpPlayer;

void BW_CleanUp() {
	free(dataUnit.exdata);
	delete dataUnit.myPlayer;
	//free(dataUnit.exdata->toServer);
	free(dataUnit.exdata->fromServer);
}

void parseString(char* string) {
	sscanf(string, "%d %d %d %d %d",&tmpPlayer.ID,&tmpPlayer.x,&tmpPlayer.y,&tmpPlayer.vx,&tmpPlayer.vy);
	if (tmpPlayer.ID != dataUnit.myID) {
		if (!dataUnit.playerStack[tmpPlayer.ID].status) {
			dataUnit.playerStack[tmpPlayer.ID].plrptr = new CPlayer(tmpPlayer.x, tmpPlayer.y);
			dataUnit.playerStack[tmpPlayer.ID].plrptr->setID(tmpPlayer.ID);
			dataUnit.playerStack[tmpPlayer.ID].plrptr->setPlVelocity(tmpPlayer.vx, tmpPlayer.vy);
			dataUnit.playerStack[tmpPlayer.ID].status = 1;
		}
		else if(dataUnit.playerStack[tmpPlayer.ID].status==1) {
			dataUnit.playerStack[tmpPlayer.ID].plrptr->setX(tmpPlayer.x);
			dataUnit.playerStack[tmpPlayer.ID].plrptr->setY(tmpPlayer.y);
			dataUnit.playerStack[tmpPlayer.ID].plrptr->setPlVelocity(tmpPlayer.vx, tmpPlayer.vy);
		}
	}
}

void saveNetworkBuff() {
		//std::cout << "I'm Updating the data!\n";
	strcpy(dataUnit.exdata->outputBackBufferptr, (std::string(dataUnit.exdata->ID) + " " + std::to_string(dataUnit.myPlayer->getX()) + " " + std::to_string(dataUnit.myPlayer->getY()) + " " + std::to_string(dataUnit.myPlayer->getVx()) + " " + std::to_string(dataUnit.myPlayer->getVy())).c_str());
	tmpbool = FP_getSendFlag();
	FP_stopSending();
	if (!FP_getSendStatus()) {
		dataUnit.exdata->tempptr = dataUnit.exdata->outputBackBufferptr;
		dataUnit.exdata->outputBackBufferptr = dataUnit.exdata->outputFrontBufferptr;
		dataUnit.exdata->outputFrontBufferptr = dataUnit.exdata->tempptr;
	}
	if (tmpbool) FP_startSending();
	//std::cout << m_struct.network_instance.sendstatus << std::endl;
	finder = (dataUnit.exdata->incomingBuffer)+5;
	//std::cout << dataUnit.exdata->incomingBuffer << std::endl;

	if ((dataUnit.exdata->incomingBuffer)[4] == '\n') {
		while (true) {
			found = strchr(finder, '\n');
			if (found) {
				*found = '\0';
				parseString(finder);
				finder = found + 1;
			}
			else {
				parseString(finder);
				break;
			}
		}
		//std::cout << finder << std::endl;
	}
}

//function responsible for drawing everything on screen
void display() {
	for (int i = 0; i < 100; i++) {
		if (dataUnit.playerStack[i].status == 1) {
			dataUnit.playerStack[i].plrptr->Draw();
		}
	}
	//std::cout << (dataUnit.exdata->toServer) << std::endl;
}

void loadData() {
	dataUnit.mastersprite = new FP_CMULTI_SPRITE("data/res/sprites/all_sprites.png", 25, 16);
}

void gameInit() {
	char host[50];
	std::cout << "Set host: ";
	std::cin >> host;
	FP_Init("BattleWorld 2015", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 576, SDL_WINDOW_SHOWN);
//	FP_Init("BattleWorld 2015", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1366, 768, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN );
	dataUnit.exdata = (fpst_network_exchange*)malloc(sizeof(fpst_network_exchange));
	(dataUnit.exdata->ID)[0] = 'n';
	(dataUnit.exdata->ID)[1] = '\0';
	for (int i = 0; i < 100; i++) {
		dataUnit.playerStack[i].status = 0;
	}
	FP_SetServer(host, 12002, dataUnit.exdata);		//Set Server Address
	dataUnit.myPlayer = new CPlayer(400,300);
	FP_startSending();	
	FP_startReceiving();
	//std::cout << strlen(dataUnit.exdata->ID) << std::endl;
	while ((dataUnit.exdata->ID)[0] == 'n') {
		std::cout << "Waiting for ID...\n" << std::endl;
		SDL_Delay(1000);
	}
	dataUnit.myID = atoi(dataUnit.exdata->ID);
	std::cout << "ID Received : " << dataUnit.myID << std::endl;
	dataUnit.playerStack[dataUnit.myID].status = 1;
	dataUnit.playerStack[dataUnit.myID].plrptr = dataUnit.myPlayer;
	dataUnit.myPlayer->setID(dataUnit.myID);
	loadData();
}

void gamePhysics() {
	dataUnit.myPlayer->controls();
	for (int i = 0; i < 100; i++) {
		if (dataUnit.playerStack[i].status == 1) {
			dataUnit.playerStack[i].plrptr->playerPhysics();
		}
	}
	saveNetworkBuff();
}
int main(int argc, char* argv[]){
	gameInit();
	FP_Loop(display, gamePhysics);
	FP_CleanUp();
	BW_CleanUp();
	return 0;
}