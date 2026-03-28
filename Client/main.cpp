#include "ConfigManager.h"
#include "ConnectionManager.h"
#include "PacketTransmitter.h"
#include "TelemetryReader.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

int main(int argc, char* argv[]) {

	//Parse config
	ConfigManager config;
	cout << "argc: " << argc << endl;
	if (!config.parse(argc, argv)) {
		
		cerr << "[ERROR] Usage: Client.exe <ServerIP> <Port> <TelemetryFile>" << endl;
		return 1;
	}

	cout << "Server IP: " << config.getServerIP() << endl;
	cout << "Data File: " << config.getFilePath() << endl;

	//Connecting to server
	ConnectionManager connection;
	if (!connection.connectToServer(config.getServerIP(), config.getPort())) {
		cerr << "Failed to connect to server." << endl;
		return 1;
	}
	cout << "Connected to server successfully." << endl;

	//Receive ID from server
	char idBuffer[32];
	int bytes = recv(connection.getSocket(), idBuffer, sizeof(idBuffer), 0);
	if (bytes <= 0) {
		cerr << "Failed to receive airplane ID\n";
		connection.disconnect();
		return 1;
	}
	idBuffer[bytes] = '\0';
	std::string airplanID = idBuffer;
	cout << "Airplane ID: " << airplanID << endl;

	//Open telemtry file
	TelemetryReader reader;
	if (!reader.openFile(config.getFilePath())) {
		cerr << "Could not open telemetry file" << config.getFilePath() << endl;
		connection.disconnect();
		return 1;
	}

	//read-packetize-transmit loop
	PacketTransmitter transmitter(connection.getSocket(), airplanID);

	string timestamp;
	double fuelRemaining;
	while (reader.readNextLine(timestamp, fuelRemaining)) {
		if (!transmitter.senPacket(timestamp, fuelRemaining)) {
			cerr << "Error Lost connection to server." << endl;
			break;
		}

		cout << "SENT: " << timestamp << ", Fuel " << fuelRemaining << endl;
		this_thread::sleep_for(chrono::seconds(1)); //simulate a 1 second delay between packets
	}
	cout << "Telemetry transmission completed. EOF reacherd." << endl;

	//cleanup
	reader.closeFile();
	connection.disconnect();

	return 0;

}