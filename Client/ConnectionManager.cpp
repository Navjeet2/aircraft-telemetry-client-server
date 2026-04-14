#include "ConnectionManager.h"
#include <iostream>
#include <WS2tcpip.h>

using namespace std;

// Constructor initializes Winsock and sets default values
ConnectionManager::ConnectionManager() : sock(INVALID_SOCKET), connected(false) {

	// Initialize Winsock library for network communication
	WSADATA wsaData;
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);

	// Check if initialization failed
	if (result != 0) {
		cerr << "WSAStartup failed: " << result << endl;
	}
}

// Destructor ensures proper cleanup of resources
ConnectionManager::~ConnectionManager() {
	disconnect();   // close connection if open
	WSACleanup();   // clean up Winsock
}

// Establishes TCP connection to server using IP and port
bool ConnectionManager::connectToServer(const string& serverIP, int port) {

	// Prevent duplicate connections
	if (connected) {
		cerr << "Already connected to a server." << endl;
		return false;
	}

	// Create TCP socket
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET) {
		cerr << "Error creating socket: " << WSAGetLastError() << endl;
		return false;
	}

	// Setup server address structure
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);

	// Converts IP string to binary format
	inet_pton(AF_INET, serverIP.c_str(), &serverAddr.sin_addr);

	// Attempts to connect to server
	int result = connect(sock, (sockaddr*)&serverAddr, sizeof(serverAddr));
	if (result == SOCKET_ERROR) {
		cerr << "Error connecting to server: " << WSAGetLastError() << endl;
		closesocket(sock);
		sock = INVALID_SOCKET;
		return false;
	}

	// Mark connection as successful
	connected = true;
	return true;
}

// Closes the connection safely
void ConnectionManager::disconnect() {

	// Only disconnects if socket is valid
	if (sock != INVALID_SOCKET) {

		// Shutdowns both send and receive
		shutdown(sock, SD_BOTH);

		// Closes socket
		closesocket(sock);

		// Resets values
		sock = INVALID_SOCKET;
		connected = false;

		cout << "Disconnected from server." << endl;
	}
}