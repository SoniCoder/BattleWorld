#include "Engine.h"

fp_main_data m_struct;

const char* sendpysocketforming = "from socket import *\n\
serverName = 'localhost'\n\
serverPort = 12002\n\
clientSocket = socket(AF_INET,SOCK_DGRAM)\n\
";

void FP_CleanUp() {
	SDL_DestroyRenderer(m_struct.renderer);
	delete m_struct.mainevent;
}



void FP_Init(const char *title,
	int x, int y, int w,
	int h, Uint32 flags){
	SDL_Init(SDL_INIT_EVERYTHING);
	Py_Initialize();
	SDL_Window* window = SDL_CreateWindow(title, x, y, w, h, flags);
	m_struct.mainevent = new SDL_Event();
	m_struct.renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	m_struct.time_unit.sdl_time = SDL_GetTicks();
	m_struct.network_instance.threadstatus = 0;
}


void FP_Loop(void(*dispfunc)(), void(*gamePhysics)()) {
	while (m_struct.mainevent->type != SDL_QUIT) {
		if (SDL_GetTicks() > m_struct.time_unit.sdl_time + 20) {
			m_struct.time_unit.sdl_time = SDL_GetTicks();
			while (SDL_PollEvent(m_struct.mainevent)) {
			}
			gamePhysics();
			dispfunc();
			SDL_RenderClear(m_struct.renderer);
			SDL_RenderPresent(m_struct.renderer);
		}
	}
	m_struct.network_instance.threadstatus = -1;
	SDL_WaitThread(m_struct.network_instance.networkRecvThread, &m_struct.network_instance.threadreturnvalue);
	SDL_WaitThread(m_struct.network_instance.networkSendThread, &m_struct.network_instance.threadreturnvalue);
	PyRun_SimpleString("clientSocket.close()");
	Py_Finalize();
}

int FP_NetworkRecvThread(void* buff) {
	while (true && !(m_struct.network_instance.threadstatus)) {
		if (!m_struct.network_instance.networkstatus) {

		}
		SDL_Delay(50);
	}
	return 0;
}

int FP_NetworkSendThread(void* buff) {
	while (true && !(m_struct.network_instance.threadstatus)) {
		if (!m_struct.network_instance.networkstatus) {
			
			PyRun_SimpleString((std::string("msg = '")+ std::string(((fpst_network_exchange*)buff)->toServer)+std::string("'")).c_str());
			PyRun_SimpleString("clientSocket.sendto(msg,(serverName, serverPort))");
			//std::cout << ((fpst_network_exchange*)buff)->toServer << std::endl;
			//std::cout << buff << std::endl ;
		}
		SDL_Delay(50);
	}
	return 0;
}

void FP_SetServer(const char* host, int port, fpst_network_exchange* exunit) {
	PyRun_SimpleString(sendpysocketforming);
	m_struct.network_instance.networkstatus = -1;
	m_struct.network_instance.networkRecvThread = SDL_CreateThread(FP_NetworkRecvThread, "ClientNetworkRecvThread", (void *)(exunit));
	m_struct.network_instance.networkSendThread = SDL_CreateThread(FP_NetworkSendThread, "ClientNetworkSendThread", (void *)(exunit));
	exunit->toServer = (char*)malloc(50);
	exunit->fromServer = (char*)malloc(50);
	strcpy(exunit->toServer, "hi");
	strcpy(exunit->fromServer, "hi");
}