

#include <WinSock2.h>
#include <iostream>
#include "ConnectionManager.h"


#pragma comment(lib, "ws2_32.lib")

int main()
{
    ConnectionManager cm;

    WSADATA wsaData;
    int initResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (initResult != 0) {
        std::cout << "WSAStartup failed\n";
        return 1;
    }

    cm.start(27000);


    WSACleanup();
}

