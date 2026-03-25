#include "FuelCalculation.h"

double FuelCalc::calculate(double fr1, double fr2) {
	double fuelCons = fr1 - fr2;
	if (fuelCons < 0) {
		return -1.0;
	}
	return fuelCons;
}