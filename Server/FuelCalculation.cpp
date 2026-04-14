#include "FuelCalculation.h"

// Calculates fuel consumed between two telemetry readings
double FuelCalc::calculate(double fr1, double fr2) {

	// Fuel consumed is the difference between previous and current fuel readings
	double fuelCons = fr1 - fr2;

	// If result is negative, returns invalid value
	// This helps avoid incorrect accumulation from bad data
	if (fuelCons < 0) {
		return -1.0;
	}

	return fuelCons;
}