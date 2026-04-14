#include "CSVWriter.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <mutex>

// Static mutex used to make file writing thread-safe
std::mutex CSVWriter::filemutex;

// Writes final flight result to CSV file
void CSVWriter::writeResult(const std::string& id, double totalFuelCons) {

	// Locks file access so only one thread writes at a time
	std::lock_guard<std::mutex> lock(filemutex);

	// Checks whether the results file already exists
	bool fileExists = std::ifstream("results.csv").good();

	// Opens file in append mode so previous results are preserved
	std::ofstream file("results.csv", std::ios::app);

	// If file cannot be opened, displays error and return
	if (!file.is_open()) {
		std::cout << "Could not open results.csv\n";
		return;
	}

	// If file does not exist yet, writes header row first
	if (!fileExists) {
		file << "AirplaneID,TotalFuelConsumed\n";
	}

	// Writes one line containing airplane ID and total fuel consumed
	file << id << "," << std::fixed << std::setprecision(4) << totalFuelCons << "\n";
}