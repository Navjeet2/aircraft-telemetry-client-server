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
	cout << "[INFO] Skipped header: " << header << endl;

	return true;
}

bool TelemetryReader::readNextLine(string& timestamp, double& fuelRemaining) {
	string line;
	if (!getline(file, line) || line.empty()) {
		return false; //EOF or empty
	}

	// Remove leading and trailing spaces from the whole line
	line.erase(0, line.find_first_not_of(" \t\r\n"));
	line.erase(line.find_last_not_of(" \t\r\n") + 1);

	if (line.empty())
	{
		return false;
	}

	//Parse CSV: expected format timestamp, fuelRemaining
	stringstream ss(line);
	string fuelStr;

	getline(ss, timestamp, ',');
	getline(ss, fuelStr, ',');

	// Trim spaces from fuelStr just in case
	fuelStr.erase(0, fuelStr.find_first_not_of(" \t"));
	fuelStr.erase(fuelStr.find_last_not_of(" \t") + 1);

	// Trim spaces from timestamp just in case
	timestamp.erase(0, timestamp.find_first_not_of(" \t"));
	timestamp.erase(timestamp.find_last_not_of(" \t") + 1);


	try {
		fuelRemaining = stod(fuelStr);
	}
	catch (...)
	{
		cerr << "Failed to parse line: " << line << endl;
		return false;
	}
	return true;
}

void TelemetryReader::closeFile() {
	if (file.is_open()) {
		file.close();
	}
}