#include "ConnectionManager.h"
#include "DataParser.h"
#include "FuelCalculation.h"
#include "CSVWriter.h"
#include <iostream>
#include <thread>

void handleClient(SOCKET clientSocket) {
    char buffer[1024];
    int bytesReceived;
    std::string airplaneID = "";
    double prevFuel = -1.0;
    double totalFuelConsuption = 0.0;

    DataParser parser;
    FuelCalc fuelCalc;
    CSVWriter csvWriter;

    while (true) {
        bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived > 0) {
            buffer[bytesReceived] = '\0';
            std::cout << buffer;
            TelemetryPacket tp = parser.parse(buffer);
            std::cout << "ID: " << tp.airplanID << "\n";
            std::cout << "TS: " << tp.timestamp << "\n";
            std::cout << "Fuel: " << tp.fuelRemaining << "\n";
            airplaneID = tp.airplanID;
            if (prevFuel > -1.0) {
                double fuelConsumed = fuelCalc.calculate(prevFuel, tp.fuelRemaining);
                if (fuelConsumed > -1.0) {
                    totalFuelConsuption += fuelConsumed;
                }
                // std::cout << "\t" << totalFuelConsuption << "\n";
            }
            prevFuel = tp.fuelRemaining;
        }
        else if (bytesReceived == 0) {
            std::cout << "Client Disconnected\n";
            csvWriter.writeResult(airplaneID, totalFuelConsuption);
            std::cout << "totalFuelConsuption has been written in CSV file.";
            break;
        }
        else {
            std::cout << "receive Error\n";
            break;
        }
    }
    closesocket(clientSocket);
}

void ConnectionManager::start(int portNumber) {

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (INVALID_SOCKET == serverSocket) {
        std::cout << "Socket creation failed\n";
        return;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(portNumber);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    int bindResult = bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
    if (SOCKET_ERROR == bindResult) {
        std::cout << "could not bind the server\n";
        closesocket(serverSocket);
        return;
    }

    int lresult = listen(serverSocket, SOMAXCONN);
    if (SOCKET_ERROR == lresult) {
        std::cout << "Server could not start listing\n";
        closesocket(serverSocket);
        return;
    }

    std::cout << "Server listening on port " << portNumber << "\n";

    sockaddr_in clientAddr;
    int clientSize = sizeof(clientAddr);
    while (true) {
        SOCKET clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientSize);

        if (INVALID_SOCKET == clientSocket) {
            std::cout << "Could not accept client connection\n";
            continue;
        }

        std::cout << "Connection Established succussfully\n";
        std::thread t(handleClient, clientSocket);
        t.detach();
    }

    closesocket(serverSocket);
}