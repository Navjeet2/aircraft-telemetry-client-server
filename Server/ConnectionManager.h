#pragma once
#include <WinSock2.h>
/// @class ConnectionManager
/// @brief Manages incoming client connections to the server.
class ConnectionManager {
	public:
		/// @brief Starts the server to listen for incoming client connections.
		///
		/// This method initializes the server socket and begins listening for incoming client connections on the specified port number. 
		/// @param int portNumber The port number on which the server will listen for incoming client connections.
		/// @return None
		void start(int portNumber);
};
/// @brief Handles communication with a connected client.
///
/// This function is responsible for managing the communication with a connected client. 
/// It should read data from the client, process it as needed, and send responses back to the client. 
/// This function is typically run in a separate thread or process for each connected client to allow for concurrent handling of multiple clients.
/// @param clientSocket The socket representing the connection to the client. 
/// @return None
void handleClient(SOCKET clientSocket);