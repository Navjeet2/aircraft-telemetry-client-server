#pragma once
#include <string>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

class ConnectionManager {
public:
	ConnectionManager();
	~ConnectionManager();

	bool connectToServer(const std::string& serverIP, int port);
	void disconnect();
	SOCKET getSocket() const { return sock; }

private:
	SOCKET sock;
	bool connected;
};