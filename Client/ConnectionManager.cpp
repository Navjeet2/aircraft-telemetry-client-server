#include "ConnectionManager.h"
#include <iostream>
#include <WS2tcpip.h>

using namespace std;

ConnectionManager::ConnectionManager() : sock(INVALID_SOCKET), connected(false) {
	// Initialize Winsock
	WSADATA wsaData;
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != 0) {
		cerr << "WSAStartup failed: " << result << endl;
	}
}

ConnectionManager::~ConnectionManager() {
	disconnect();
	WSACleanup();
}

bool ConnectionManager::connectToServer(const string& serverIP, int port) {
	if (connected) {
		cerr << "Already connected to a server." << endl;
		return false;
	}
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET) {
		cerr << "Error creating socket: " << WSAGetLastError() << endl;
		return false;
	}
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	inet_pton(AF_INET, serverIP.c_str(), &serverAddr.sin_addr);
	int result = connect(sock, (sockaddr*)&serverAddr, sizeof(serverAddr));
	if (result == SOCKET_ERROR) {
		cerr << "Error connecting to server: " << WSAGetLastError() << endl;
		closesocket(sock);
		sock = INVALID_SOCKET;
		return false;
	}
	connected = true;
	return true;
}

void ConnectionManager::disconnect() {
	if (sock!=INVALID_SOCKET) {
		shutdown(sock, SD_BOTH);
		closesocket(sock);
		sock = INVALID_SOCKET;
		connected = false;
		cout << "Disconnected from server." << endl;
	}
}