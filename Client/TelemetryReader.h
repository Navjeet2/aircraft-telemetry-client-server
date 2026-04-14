#pragma once
#include <string>
#include <fstream>

using namespace std;
/// @class TelemetryReader
/// @brief Manages reading telemetry data from a file.
class TelemetryReader {
public:
	/// @brief Opens the telemetry file for reading.
	///
	/// This method attempts to open the specified file path for reading telemetry data. It returns true if the file was successfully opened, and false if there was an error (e.g., file not found, permission issues).
	/// @param string filepath The path to the telemetry file to be opened.
	/// @return True if the file was opened successfully, false otherwise.

	bool openFile(const string& filepath);
	/// @brief Reads the next line of telemetry data from the file.
	///
	/// This method reads the next line from the opened telemetry file and parses it to extract the timestamp and fuel remaining information. 
	/// @param string timestamp, double fuelRemaining The variables to store the parsed timestamp and fuel remaining values. 
	bool readNextLine(string& timestamp, double& fuelRemaining);
	/// @brief Closes the telemetry file.
	///
	/// This method closes the telemetry file if it is currently open. 
	/// It should be called when the telemetry data reading is complete or if an error occurs that requires closing the file.
	/// @param None
	/// @return None
	void closeFile();

private:
	ifstream file;
};