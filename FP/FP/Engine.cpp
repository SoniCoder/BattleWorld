#include "Engine.h"

fp_main_data m_struct;



void FP_CleanUp() {
	SDL_DestroyRenderer(m_struct.renderer);
	delete m_struct.mainevent;
}

int fp_float_to_int_width(float f) {
	return (int)(f*m_struct.window.w);
}

int fp_float_to_int_height(float f) {
	return (int)(f*m_struct.window.h);
}


void FP_Init(const char *title,
	int x, int y, int w,
	int h, Uint32 flags){
	SDL_Init(SDL_INIT_EVERYTHING);
	//Py_Initialize();
	SDL_Window* window = SDL_CreateWindow(title, x, y, w, h, flags);
	m_struct.mainevent = new SDL_Event();
	m_struct.renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	m_struct.time_unit.sdl_time = SDL_GetTicks();
	m_struct.network_instance.threadstatus = 0;
	m_struct.window.w = w;
	m_struct.window.h = h;
	m_struct.window.wtostd = w / 1024.0;
	m_struct.handlers.keyhandler = (void*)(new CKeyboardHandler());
}


void FP_Loop(void(*dispfunc)(), void(*gamePhysics)()) {
	while (m_struct.mainevent->type != SDL_QUIT) {
		if (SDL_GetTicks() > m_struct.time_unit.sdl_time + 17) {
			m_struct.time_unit.sdl_time = SDL_GetTicks();
			if(SDL_PollEvent(m_struct.mainevent)) {
				if (m_struct.mainevent->type == SDL_KEYDOWN)
				{
					((CKeyboardHandler*)(m_struct.handlers.keyhandler))->setstate(m_struct.mainevent->key.keysym.scancode, SDL_PRESSED);
					
				}
				if (m_struct.mainevent->type == SDL_KEYUP)
				{
					((CKeyboardHandler*)(m_struct.handlers.keyhandler))->setstate(m_struct.mainevent->key.keysym.scancode, SDL_RELEASED);
				}
				
			}
			SDL_RenderClear(m_struct.renderer);
			dispfunc();
			SDL_RenderPresent(m_struct.renderer);
			gamePhysics();
			
		}
	}
	m_struct.network_instance.threadstatus = -1;
	SDL_WaitThread(m_struct.network_instance.networkRecvThread, &m_struct.network_instance.threadreturnvalue);
	SDL_WaitThread(m_struct.network_instance.networkSendThread, &m_struct.network_instance.threadreturnvalue);
	//PyRun_SimpleString("clientSocket.close()");
	//Py_Finalize();
}

int FP_NetworkRecvThread(void* buff) {
	using boost::asio::ip::udp;
	boost::asio::io_service io_service;
	m_struct.network_instance.recsocket = new udp::socket(io_service, udp::endpoint(udp::v4(), 12006));
	char buffc[64] = { '\0' };
	udp::endpoint sender;
	int bufferlength;
	while (true && !(m_struct.network_instance.threadstatus)) {
		if (!m_struct.network_instance.networkstatus) {
			//PyRun_SimpleString("print 'recv thread'");
			//m_struct.network_instance.recsocket->receive(boost::asio::buffer(buffc));
			bufferlength = m_struct.network_instance.recsocket->available();
			if (bufferlength) {
				m_struct.network_instance.recsocket->receive_from(boost::asio::buffer(buffc, sizeof(buffc)), sender);
				buffc[bufferlength] = { '\0' };
				std::cout << buffc << std::endl;
				std::cout << sender.address().to_string() << "    "<< bufferlength << std::endl;
				m_struct.network_instance.sendstatus = 0;
			}
		}
	}
	return 0;
}

int FP_NetworkSendThread(void* buff) {
	using boost::asio::ip::udp;
	boost::asio::io_service io_service;
	m_struct.network_instance.sendsocket = new udp::socket(io_service, udp::endpoint(udp::v4(), 12004));
	udp::resolver resolver(io_service);
	udp::resolver::query query(udp::v4(), "localhost", "12002");
	m_struct.network_instance.sv_endpt = *resolver.resolve(query);
	while (true && !(m_struct.network_instance.threadstatus)) {
		if (!m_struct.network_instance.networkstatus && !m_struct.network_instance.sendstatus) {
			m_struct.network_instance.sendsocket->send_to(boost::asio::buffer(std::string(((fpst_network_exchange*)buff)->toServer)), m_struct.network_instance.sv_endpt);
			m_struct.network_instance.sendstatus = -1;
		}
		SDL_Delay(30);
	}
	return 0;
}

void FP_SetServer(const char* host, int port, fpst_network_exchange* exunit) {
	/*PyRun_SimpleString("from socket import *");
	PyRun_SimpleString(("serverName = '" + std::string(host) + "'").c_str());
	PyRun_SimpleString("serverPort = 12002");
	PyRun_SimpleString("clientSocket = socket(AF_INET,SOCK_DGRAM)");*/
	m_struct.network_instance.host = host;
	m_struct.network_instance.networkstatus = -1;
	m_struct.network_instance.sendstatus = 0;
	m_struct.network_instance.networkRecvThread = SDL_CreateThread(FP_NetworkRecvThread, "ClientNetworkRecvThread", (void *)(exunit));
	m_struct.network_instance.networkSendThread = SDL_CreateThread(FP_NetworkSendThread, "ClientNetworkSendThread", (void *)(exunit));
	exunit->toServer = (char*)malloc(50);
	exunit->fromServer = (char*)malloc(50);
	strcpy(exunit->toServer, "N");
	strcpy(exunit->fromServer, "Initial Input Buffer");
}