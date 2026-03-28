#include "CSVWriter.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <mutex>

std::mutex CSVWriter::filemutex;

void CSVWriter::writeResult(const std::string& id, double totalFuelCons) {
	std::lock_guard<std::mutex> lock(filemutex);
	bool fileExists = std::ifstream("results.csv").good();
	std::ofstream file("results.csv", std::ios::app);
	if (!file.is_open()) {
		std::cout << "Could not open results.csv\n";
		return;
	}
	if (!fileExists) {
		file << "AirplaneID,TotalFuelConsumed\n";
	}
	file << id << "," << std::fixed << std::setprecision(4) << totalFuelCons << "\n";
}