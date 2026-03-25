#include "DataParser.h"
#include <sstream>

TelemetryPacket DataParser::parse(const std::string& rawData) {
	TelemetryPacket tp;
	
	std::stringstream ss(rawData);

	std::string fuelStr;

	getline(ss, tp.airplanID, ',');
	getline(ss, tp.timestamp, ',');
	getline(ss, fuelStr, ',');

	tp.fuelRemaining = std::stod(fuelStr);

	return tp;
}
