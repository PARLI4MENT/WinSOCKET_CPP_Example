// ClientC.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <WinSock2.h>
//#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)

SOCKET Connection;

void ClientHandler() {
    char msg[256];
    while (true){
        recv(Connection, msg, sizeof(msg), NULL);
        std::cout << msg << std::endl;
    }
}

int main()
{
    WSADATA wsaData;
    WORD DLLVersion = MAKEWORD(2, 1);

    if (WSAStartup(DLLVersion, &wsaData) != 0) {
        std::cout << "WSAStartup Error!\n";
        exit(1);
    }

    SOCKADDR_IN addr;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(1111);
    addr.sin_family = AF_INET;

    Connection = socket(AF_INET, SOCK_STREAM, NULL);
    if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
        std::cout << "Error: failed connect to Server!\n";
        return 1;
    }

    std::cout << "Connect for Server is Done!\n";

    CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, NULL, NULL, NULL);

    char msg[256];
    while (true) {
        std::cin.getline(msg, sizeof(msg));
        send(Connection, msg, sizeof(msg), NULL);
        Sleep(10);
    }

    system("pause");
    return 0;
}