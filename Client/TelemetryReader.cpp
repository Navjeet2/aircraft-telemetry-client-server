#include "TelemetryReader.h"
#include <iostream>
#include <sstream>

using namespace std;

bool TelemetryReader::openFile(const string& filePath) {
	file.open(filePath);
	if (!file.is_open()) {
		 
		cerr << "[ERROR] Cannot open file: " << filePath << endl;
		return false;
	}

	//skip header line if present
	string header;
	getline(file, header);

	return true;
}

bool TelemetryReader::readNextLine(string& timestamp, double& fuelRemaining) {
	string line;
	if (!getline(file, line) || line.empty()) {
		return false; //EOF or empty
	}

	//Parse CSV: expected format timestamp, fuelRemaining
	stringstream ss(line);
	string fuelStr;

	getline(ss, timestamp, ',');
	getline(ss, fuelStr, ',');

	try {
		fuelRemaining = stod(fuelStr);
	}
	catch (...)
	{
		cerr << "[WARN] Failed to parse line: " << line << endl;
		return false;
	}
	return true;
}

void TelemetryReader::closeFile() {
	if (file.is_open()) {
		file.close();
	}
}