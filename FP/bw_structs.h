#ifndef GAME_STRUCTS
#define GAME_STRUCTS

#include "Player.h"
struct player {
	int ID;
	int status;
	int x;
	int y;
	int vx;
	int vy;
	CPlayer* plrptr;
};


struct mainData {
	CPlayer* myPlayer;
	fpst_network_exchange* exdata;
	FP_CMULTI_SPRITE* mastersprite;
	int myID;
	struct player playerStack[100];
};

#endif