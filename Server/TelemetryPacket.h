#pragma once

#include <string>

struct TelemetryPacket {
	std::string airplanID;
	std::string timestamp;
	double fuelRemaining;
};


