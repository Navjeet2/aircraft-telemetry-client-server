#include "ConnectionManager.h"
#include "DataParser.h"
#include "FuelCalculation.h"
#include "CSVWriter.h"
#include <iostream>
#include <thread>

// This function handles communication with one connected client
void handleClient(SOCKET clientSocket) {
    char buffer[1024];
    int bytesReceived;

    // Variables used to track the client flight session
    std::string airplaneID = "";
    double prevFuel = -1.0;
    double totalFuelConsuption = 0.0;

    // Create helper module objects for parsing, calculation, and file writing
    DataParser parser;
    FuelCalc fuelCalc;
    CSVWriter csvWriter;

    // Keep receiving telemetry data until the client disconnects or an error occurs
    while (true) {
        bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);

        if (bytesReceived > 0) {
            // Null-terminate received data so it can be treated as a string
            buffer[bytesReceived] = '\0';

            // Parse the incoming telemetry packet
            TelemetryPacket tp = parser.parse(buffer);

            // Store airplane ID from the received packet
            airplaneID = tp.airplanID;

            // If this is not the first reading, calculate fuel consumed
            if (prevFuel > -1.0) {
                double fuelConsumed = fuelCalc.calculate(prevFuel, tp.fuelRemaining);

                // Only add valid fuel consumption values
                if (fuelConsumed > -1.0) {
                    totalFuelConsuption += fuelConsumed;
                }
            }

            // Update previous fuel value for next calculation
            prevFuel = tp.fuelRemaining;
        }
        else if (bytesReceived == 0) {
            // Client disconnected normally
            std::cout << airplaneID << " Disconnected\n";

            // Write final result to CSV when flight ends
            csvWriter.writeResult(airplaneID, totalFuelConsuption);
            std::cout << "totalFuelConsuption for " << airplaneID << " has been written in CSV file.\n";
            break;
        }
        else {
            // recv() timed out or an unexpected connection error occurred
            std::cout << airplaneID << " connection lost\n";
            break;  // Exit the thread and release memory
        }
    }

    // Close the client socket after communication ends
    closesocket(clientSocket);
}

// Starts the server and listens for incoming client connections
void ConnectionManager::start(int portNumber) {

    // Creates TCP server socket
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (INVALID_SOCKET == serverSocket) {
        std::cout << "Socket creation failed\n";
        return;
    }

    // Configures server address information
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(portNumber);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Binds socket to the given port
    int bindResult = bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
    if (SOCKET_ERROR == bindResult) {
        std::cout << "could not bind the server\n";
        closesocket(serverSocket);
        return;
    }

    // Puts server socket into listening mode
    int lresult = listen(serverSocket, SOMAXCONN);
    if (SOCKET_ERROR == lresult) {
        std::cout << "Server could not start listing\n";
        closesocket(serverSocket);
        return;
    }

    std::cout << "Server listening on port " << portNumber << "\n";

    sockaddr_in clientAddr;
    int clientSize = sizeof(clientAddr);
    int clientCounter = 0;

    // Keeps accepting clients continuously
    while (true) {
        SOCKET clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientSize);

        // If accept fails, continues waiting for new clients
        if (INVALID_SOCKET == clientSocket) {
            std::cout << "Could not accept client connection\n";
            continue;
        }

        std::cout << "Connection Established succussfully\n";

        // Sets a receive timeout so dead clients do not block forever
        int timeout = 5000; // 5 seconds 
        setsockopt(clientSocket, SOL_SOCKET, SO_RCVTIMEO,
            (char*)&timeout, sizeof(timeout));

        // Assigns a temporary unique airplane ID for each connected client
        clientCounter++;
        std::string assignedID = "PLANE-0" + std::to_string(clientCounter);
        send(clientSocket, assignedID.c_str(), assignedID.size(), 0);
        std::cout << "Server has assigned Id : " << assignedID << "\n";

        // Creates a separate thread for this client so multiple clients can run in parallel
        std::thread t(handleClient, clientSocket);
        t.detach();
    }

    // Closes server socket if the loop ever exits
    closesocket(serverSocket);
}