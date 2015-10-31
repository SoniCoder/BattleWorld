#ifndef FP_STRUCTS
#define FP_STRUCTS
struct fpst_network {
	SDL_Thread *networkSendThread;
	SDL_Thread *networkRecvThread;
	int networkstatus;
	int threadstatus;
	int threadreturnvalue;
};
struct fpst_network_exchange {
	char* toServer;
	char* fromServer;
};
struct fpst_time {
	Uint32 sdl_time;
};
struct fp_main_data {
	SDL_Renderer* renderer;
	SDL_Event* mainevent;
	fpst_network network_instance;
	fpst_time time_unit;
};
#endif
