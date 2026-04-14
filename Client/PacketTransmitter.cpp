#include "PacketTransmitter.h"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

// Constructor initializes the socket and assigns the airplane ID
PacketTransmitter::PacketTransmitter(SOCKET socket, const string& airplane_id) :
	sock(socket), airplaneID(airplane_id) {
}

//Builds and sends a telemetry packet to the server
bool PacketTransmitter::senPacket(const string& timestamp, double fuelRemaining) {

	// Creates a formatted packet using string stream
	// Format: airplaneID,timestamp,fuelRemaining
	ostringstream packet;
	packet << airplaneID << ","
		<< timestamp << ","
		<< fixed << setprecision(2) // ensures fuel value is 2 decimal places
		<< fuelRemaining << "\n";

	// Converts stream into string for transmission
	string data = packet.str();

	// Sends packet through TCP socket
	int bytesSent = send(sock, data.c_str(), (int)data.size(), 0);

	// Checks if send failed
	if (bytesSent == SOCKET_ERROR) {
		cerr << "[ERROR] Failed to send packet: " << WSAGetLastError() << endl;
		return false;
	}

	// Returns true if packet sent successfully
	return true;
}