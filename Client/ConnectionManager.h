#pragma once
#include <string>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
/// @class ConnectionManager
/// @brief Manages the connection.
///
/// Manages the connection to the server, including establishing and closing the socket connection.
class ConnectionManager {
public:
	ConnectionManager();
	~ConnectionManager();
	/// @brief Connects to the server.
	/// 
	/// Connects to the server using the provided IP address and port number. Returns true if the connection is successful, false otherwise.
	/// @param serverIP The IP address of the server to connect to.
	/// @param port The port number to connect to on the server.
	/// @return True if the connection was successful, false otherwise.
	bool connectToServer(const std::string& serverIP, int port);

	/// @brief Disconnects from the server.
	///
	/// Disconnects from the server by closing the socket connection and cleaning up resources. After calling this method, the ConnectionManager will no longer be connected to the server.
	/// @param None
	/// @return None
	void disconnect();
	/// @brief Gets the socket.
	///
	/// Returns the socket used for the connection to the server. This socket can be used for sending and receiving data. If the connection is not established, this method may return an invalid socket.
	/// @param None
	/// @return The socket used for the connection to the server.
	SOCKET getSocket() const { return sock; }

private:
	SOCKET sock;
	bool connected;
};