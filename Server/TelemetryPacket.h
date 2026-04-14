#pragma once

#include <string>
/// @struct TelemetryPacket
/// @brief Represents a telemetry packet containing airplane ID, timestamp, and fuel remaining information.
struct TelemetryPacket {
	std::string airplanID;
	std::string timestamp;
	double fuelRemaining;
};


