#pragma once

#include "TelemetryPacket.h"

class DataParser {
public:
	TelemetryPacket parse(const std::string& s);
};
