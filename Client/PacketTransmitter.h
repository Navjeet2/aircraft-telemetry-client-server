#pragma once
#include <string>
#include <WinSock2.h>

using namespace std;
class PacketTransmitter {
	public:
		PacketTransmitter(SOCKET socket, const string& airplane_id);
		bool senPacket(const string& timestamp, double fuelReamining);

private:
	SOCKET sock;
	string airplaneID;
};