#include <iostream>
#include "Engine.h"
int main(int argc, char* argv[]){
	FP_Init("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	FP_Loop();
	return 0;
}