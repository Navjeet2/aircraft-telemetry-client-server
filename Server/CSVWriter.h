#pragma once
#include <string>
#include <mutex>

class CSVWriter {
	public:
		void writeResult(const std::string& id, double totalFuelCons);
	private:
		static std::mutex filemutex;
};