#pragma once

#include "TelemetryPacket.h"
/// @class DataParser
/// @brief Manages parsing telemetry data from a string.
class DataParser {
public:
	/// @brief Parses a string to extract telemetry data.
	///
	/// This method takes a string input, which is expected to contain telemetry data in a specific format. 
	/// It parses the string to extract the timestamp and fuel remaining values, and returns a TelemetryPacket object containing this information. 
	/// @param string containing the telemetry data to be parsed.
	/// @return A TelemetryPacket object containing the parsed timestamp and fuel remaining values.
	TelemetryPacket parse(const std::string& s);
};
