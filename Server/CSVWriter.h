#pragma once
#include <string>
#include <mutex>
/// @class CSVWriter
/// @brief Manages writing results to a CSV file.
class CSVWriter {
	public:
		/// @brief Writes the result to a CSV file.
		///
		/// This method takes the airplane ID and total fuel consumption, and writes them to a CSV file in a thread-safe manner.
		/// @param string id The airplane ID to be written to the CSV file.
		/// @param double totalFuelCons The total fuel consumption to be written to the CSV file.
		/// @return None
		void writeResult(const std::string& id, double totalFuelCons);
	private:
		static std::mutex filemutex;
};