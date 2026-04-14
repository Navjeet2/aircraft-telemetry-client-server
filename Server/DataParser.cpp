#include "DataParser.h"
#include <sstream>

// Parses a raw telemetry string into a TelemetryPacket object
TelemetryPacket DataParser::parse(const std::string& rawData) {
	TelemetryPacket tp;

	// Creates a string stream from the raw incoming packet
	std::stringstream ss(rawData);

	std::string fuelStr;

	// Extracst comma-separated values in order:
	// airplane ID, timestamp, fuel remaining
	getline(ss, tp.airplanID, ',');
	getline(ss, tp.timestamp, ',');
	getline(ss, fuelStr, ',');

	// Converts fuel value from string to double
	tp.fuelRemaining = std::stod(fuelStr);

	return tp;
}