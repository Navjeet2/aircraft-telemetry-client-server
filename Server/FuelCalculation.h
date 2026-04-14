#pragma once
/// @class FuelCalc
/// @brief Manages fuel consumption calculation based on telemetry data.
class FuelCalc {
	public:
		/// @brief Calculates the fuel consumption based on two fuel remaining values.
		///
		/// This method calculates the fuel consumption by taking two fuel remaining values. 
		/// The result represents the amount of fuel consumed between the two readings.
		/// @param double first fuel remaining value, double second fuel remaining value.
		/// @return The calculated fuel consumption as a double value.
		double calculate(double fr1, double fr2);
};