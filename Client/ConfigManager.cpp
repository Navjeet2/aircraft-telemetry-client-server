#include "ConfigManager.h"
#include <iostream>

// Parses command-line arguments to configure client settings
bool ConfigManager::parse(int agrc, char* argv[]) {

	// Ensures correct number of arguments are provided
	// Expected format: <server_ip> <port> <file_path>
	if (agrc != 4) {
		cerr << "Usage: " << argv[0] << " <server_ip> <port> <file_path>" << endl;
		return false;
	}

	// Assign values from command line arguments
	serverIP = argv[1];       // server IP address
	port = stoi(argv[2]);     // converts port from string to integer
	filePath = argv[3];       // path to telemetry data file

	return true;
}