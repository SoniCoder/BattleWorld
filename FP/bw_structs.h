#ifndef GAME_STRUCTS
#define GAME_STRUCTS

#include "Player.h"

struct mainData {
	CPlayer* myPlayer;
	fpst_network_exchange* exdata;
	FP_CMULTI_SPRITE* mastersprite;
};

#endif