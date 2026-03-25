#include "PacketTransmitter.h"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

PacketTransmitter::PacketTransmitter(SOCKET socket, const string& airplane_id) :
	sock(socket), airplaneID(airplane_id){
}

bool PacketTransmitter::senPacket(const string& timestamp, double fuelRemaining) {
	ostringstream packet;
	packet<< airplaneID <<","
		<< timestamp << ","
		<< fixed <<setprecision(2)
		<< fuelRemaining << "\n";

	string data = packet.str();

	int bytesSent = send(sock, data.c_str(), (int)data.size(), 0);
	if (bytesSent == SOCKET_ERROR) {
		cerr << "[ERROR] Failed to send packet: " << WSAGetLastError() << endl;
		return false;
	}

	return true;

}