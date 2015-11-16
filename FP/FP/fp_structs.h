#ifndef FP_STRUCTS
#define FP_STRUCTS

#include "Engine.h"

struct fpst_network {
	SDL_Thread *networkSendThread;
	SDL_Thread *networkRecvThread;
	//int networkstatus;
	int threadstatus;
	int sendstatus;
	bool sendflag;
	bool recvstatus;
	bool recvflag;
	int threadreturnvalue;
	const char* host;
	boost::asio::ip::udp::socket* recsocket;
	boost::asio::ip::udp::socket* sendsocket;
	boost::asio::ip::udp::endpoint sv_endpt;
};
struct fpst_network_exchange {
	//char* toServer;
	char outputFrontBuffer[1024];
	char* outputFrontBufferptr;
	char* outputBackBufferptr;
	char outputBackBuffer[1024];
	char* tempptr;
	char* fromServer;
	char incomingBuffer[2048];
	char ID[3];
};
struct fpst_time {
	Uint32 sdl_time;
};
struct fp_window {
	int w;
	int h;
	float wtostd;
};
struct fp_handlers {
	void* keyhandler;
};
struct fp_main_data {
	SDL_Renderer* renderer;
	SDL_Event* mainevent;
	fpst_network network_instance;
	fpst_time time_unit;
	fp_window window;
	fp_handlers handlers;
};
#endif
