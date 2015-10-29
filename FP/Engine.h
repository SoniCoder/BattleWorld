#ifndef FP_ENGINE
#define FP_ENGINE
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "fp_structs.h"
void FP_Init(const char *title,
	int x, int y, int w,
	int h, Uint32 flags);
void FP_Loop();
#endif