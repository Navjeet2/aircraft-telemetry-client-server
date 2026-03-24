#include "ConfigManager.h"
#include "ConnectionManager.h"
#include "PacketTransmitter.h"
#include "TelemetryReader.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {

	//Parse config
	ConfigManager config;
	if (!config.parse(argc, argv)) {
		
		cerr << "[ERROR] Usage: Client.exe <ServerIP> <Port> <TelemetryFile> <AirplaceID>" << endl;
		return 1;
	}

	cout << "Airplane ID: " << config.getAirplaneID() << endl;
	cout << "Server IP: " << config.getServerIP() << endl;
	cout << "Data File: " << config.getFilePath() << endl;

	//Connecting to server
	ConnectionManager connection;
	if (!connection.connectToServer(config.getServerIP(), config.getPort())) {
		cerr << "Failed to connect to server." << endl;
		return 1;
	}
	cout << "Connected to server successfully." << endl;

	//Open telemtry file
	TelemetryReader reader;
	if (!reader.openFile(config.getFilePath())) {
		cerr << "Could not open telemetry file" << config.getFilePath() << endl;
		connection.disconnect();
		return 1;
	}

	//read-packetize-transmit loop
	PacketTransmitter transmitter(connection.getSocket(), config.getAirplaneID());

	string timestamp;
	double fuelRemaining;
	while (reader.readNextLine(timestamp, fuelRemaining)) {
		if (!transmitter.senPacket(timestamp, fuelRemaining)) {
			cerr << "Error Lost connection to server." << endl;
			break;
		}
	}
	cout << "Telemetry transmission completed. EOF reacherd." << endl;

	//cleanup
	reader.closeFile();
	connection.disconnect();

	return 0;

}