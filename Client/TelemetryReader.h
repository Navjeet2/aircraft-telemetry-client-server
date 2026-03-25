#pragma once
#include <string>
#include <fstream>

using namespace std;

class TelemetryReader {
public:
	bool openFile(const string& filepath);
	bool readNextLine(string& timestamp, double& fuelRemaining);
	void closeFile();

private:
	ifstream file;
};