#include "Engine.h"

fp_main_struct m_struct;

void FP_Init(const char *title,
	int x, int y, int w,
	int h, Uint32 flags){
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow(title, x, y, w, h, flags);
	m_struct.renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	m_struct.mainevent = new SDL_Event();
	m_struct.sdl_time = SDL_GetTicks();
}

void FP_Loop() {
	while (m_struct.mainevent->type != SDL_QUIT) {
		SDL_PollEvent(m_struct.mainevent);
		SDL_RenderClear(m_struct.renderer);
		SDL_RenderPresent(m_struct.renderer);
	}
}