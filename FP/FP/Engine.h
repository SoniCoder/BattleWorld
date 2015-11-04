#ifndef FP_ENGINE
#define FP_ENGINE
#include <iostream>
#include <string>
#include <Python.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <boost/asio.hpp>

#include "KeyboardHandler.h"
#include "fp_majorincludes.h"
#include "FP_Network.h"
#include "fp_typedefs.h"
#include "fp_structs.h"

#include "FP_Media.h"
#include "handlerFunctions.h"


extern fp_main_data m_struct;

int fp_float_to_int_width(float f);
int fp_float_to_int_height(float f);

void FP_CleanUp();
void FP_Init(const char *title,
	int x, int y, int w,
	int h, Uint32 flags);
void FP_Loop(void (*dispfunc)(), void(*gamePhysics)());
void FP_SetServer(const char* host,int port, fpst_network_exchange* exunit);
int FP_NetworkThread(void* data);
#endif