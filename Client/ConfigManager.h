#pragma once
#include <string>

using namespace std;

class ConfigManager {
public:
	bool parse(int agrc, char* argv[]);
	string getServerIP() const { return serverIP; }
	int getPort() const { return port; }
	string getFilePath() const { return filePath; }
	string getAirplaneID() const { return airplaneID; }

private:
	string serverIP;
	int port;
	string filePath;
	string airplaneID;

};