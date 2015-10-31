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
	strcpy(dataUnit.exdata->toServer, (std::to_string(dataUnit.myPlayer->getX()) + " " + std::to_string(dataUnit.myPlayer->getY())).c_str());
}
//function responsible for drawing everything on screen
void display() {
	//std::cout << (dataUnit.exdata->toServer) << std::endl;
}

void gameInit() {
	FP_Init("BattleWorld 2015", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	dataUnit.exdata = (fpst_network_exchange*)malloc(sizeof(fpst_network_exchange));
	FP_SetServer("localhost", 12002, dataUnit.exdata);		//Set Server Address
	dataUnit.myPlayer = new CPlayer(400,300);
	FP_setNetworkStatus(0);
	
}

void gamePhysics() {
	//std::cout << (int)dataUnit.exdata->toServer << std::endl;
	saveNetworkBuff();
}

int main(int argc, char* argv[]){
	gameInit();
	//std::cout << (int)((dataUnit.exdata)->toServer) << std::endl;
	FP_Loop(display, gamePhysics);
	FP_CleanUp();
	BW_CleanUp();
	return 0;
}