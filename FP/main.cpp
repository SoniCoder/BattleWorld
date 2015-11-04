#include "Engine.h"
#include "Player.h"
#include "bw_structs.h"

//all the ingame data is shared here among functions
mainData dataUnit;

void BW_CleanUp() {
	free(dataUnit.exdata);
	delete dataUnit.myPlayer;
	free(dataUnit.exdata->toServer);
	free(dataUnit.exdata->fromServer);
}

void saveNetworkBuff() {
	strcpy(dataUnit.exdata->toServer, (std::to_string(dataUnit.myPlayer->getX()) + " " + std::to_string(dataUnit.myPlayer->getY())+" "+std::to_string(dataUnit.myPlayer->getVx()) + " " + std::to_string(dataUnit.myPlayer->getVy())).c_str());
}

//function responsible for drawing everything on screen
void display() {
	dataUnit.myPlayer->Draw();
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
	FP_SetServer(host, 12002, dataUnit.exdata);		//Set Server Address
	dataUnit.myPlayer = new CPlayer(400,300);
	//dataUnit.myPlayer->setWidth(0.05);
	//dataUnit.myPlayer->setHeight(0.05);
	FP_setNetworkStatus(0);
	loadData();
}

void gamePhysics() {
	dataUnit.myPlayer->playerPhysics();
	saveNetworkBuff();
}
int main(int argc, char* argv[]){
	gameInit();
	FP_Loop(display, gamePhysics);
	FP_CleanUp();
	BW_CleanUp();
	return 0;
}