#pragma once
#include <WinSock2.h>

class ConnectionManager {
	public:
		void start(int portNumber);
};

void handleClient(SOCKET clientSocket);