#ifndef FP_ENGINE
#define FP_ENGINE
#include <iostream>
///*
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <Python.h>
#include <string>
//*/
/*
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
*/

#include "fp_majorincludes.h"
#include "FP_Network.h"
#include "fp_typedefs.h"

void FP_CleanUp();
void FP_Init(const char *title,
	int x, int y, int w,
	int h, Uint32 flags);
void FP_Loop(void (*dispfunc)(), void(*gamePhysics)());
void FP_SetServer(const char* host,int port, fpst_network_exchange* exunit);
int FP_NetworkThread(void* data);
#endif