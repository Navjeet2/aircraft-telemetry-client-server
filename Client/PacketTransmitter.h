#pragma once
#include <string>
#include <WinSock2.h>
/// @class PacketTransmitter
/// @brief Manages packet transmission to the server.
using namespace std;
class PacketTransmitter {
	public:
		/// @brief Constructs a PacketTransmitter with the given socket and airplane ID.
		///
		/// This constructor initializes the PacketTransmitter with a socket for communication and an airplane ID to identify the source of the packets. The socket should already be connected to the server before creating an instance of PacketTransmitter.
		/// @param socker, airplane_id The socket for communication and the airplane ID to identify the source of the packets.
		/// @return None
		PacketTransmitter(SOCKET socket, const string& airplane_id);
		/// @brief Sends a packet to the server.
		///
		/// This method constructs a packet containing the timestamp and fuel remaining information, and sends it to the server using the established socket connection. The packet format can be defined as needed, but it should include the timestamp and fuel remaining data in a way that the server can parse it correctly.
		/// @param timestamp, fuelReamining The timestamp and fuel remaining information to be included in the packet.
		/// @return True if the packet was sent successfully, false otherwise.
		bool senPacket(const string& timestamp, double fuelReamining);

private:
	SOCKET sock;
	string airplaneID;
};