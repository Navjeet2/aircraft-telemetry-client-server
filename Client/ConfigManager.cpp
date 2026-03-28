#include "ConfigManager.h"
#include <iostream>

bool ConfigManager::parse(int agrc, char* argv[]) {
	if (agrc != 4) {
		cerr << "Usage: " << argv[0] << " <server_ip> <port> <file_path>" << endl;
		return false;
	}
	serverIP = argv[1];
	port = stoi(argv[2]);
	filePath = argv[3];
	return true;
}