#pragma once
#include <string>

using namespace std;

/// @class ConfigManager
/// @brief Manages configuration parsing and provides access to configuration parameters.
class ConfigManager {
public:
	/// @brief Parses command-line arguments to extract configuration parameters.
	/// 
	/// This method processes the provided argc and argv to set the server IP,
    /// port, and file path. Returns true if all required parameters are successfully parsed.
	/// @param agrc The number of command-line arguments.
	/// @param argv The array of command-line argument strings.
	/// @return True if parsing was successful, false otherwise.
	bool parse(int agrc, char* argv[]);
	/// @brief Gets the server IP address.
	/// 
	/// Returns the IP address of the server as parsed from the command-line arguments.
	/// @return The server IP as a string.
	string getServerIP() const { return serverIP; }
	/// @brief Gets the server port.
	/// 
	/// Returns the port number as parsed from the command-line arguments.
	/// @return The port number.
	int getPort() const { return port; }
	/// @brief Gets the file path.
	/// 
   /// Returns the file path as parsed from the command-line arguments.
   /// @return The file path as a string.
	string getFilePath() const { return filePath; }

private:
	string serverIP;
	int port;
	string filePath;

};