#include "FP_Network.h"


void FP_setNetworkStatus(int status) {
	m_struct.network_instance.networkstatus = status;
	return;
}