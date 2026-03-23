#include "ConfigManager.h"
#include <iostream>

bool ConfigManager::parse(int agrc, char* argv[]) {
	if (agrc != 5) {
		cerr << "Usage: " << argv[0] << " <server_ip> <port> <file_path> <airplane_id>" << endl;
		return false;
	}
	serverIP = argv[1];
	port = stoi(argv[2]);
	filePath = argv[3];
	airplaneID = argv[4];
	return true;
}