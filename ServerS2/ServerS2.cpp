// ServerS.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

#pragma warning(disable: 4996)

SOCKET Connection[100];
UINT32 Count = 0;

void ClientHandler(int index){
    char msg[256];
    while (true) {
        recv(Connection[index], msg, sizeof(msg), NULL);

        for (size_t i = 0; i < Count;i++) {
            if (i == index) {
                continue;
            }
            
            send(Connection[i], msg, sizeof(msg), NULL);
        }
    }
}

int main(int args, char* argv[])
{
    WSADATA wsaData;
    WORD DLLVersion = MAKEWORD(2, 1);
    if (WSAStartup(DLLVersion, &wsaData) != 0) {
        std::cout << "WSAStartup Error!" << std::endl;
        exit(1);
    }

    SOCKADDR_IN addr;
    int sizeofaddr = sizeof(addr);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(1111);
    addr.sin_family = AF_INET;

    SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
    bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
    listen(sListen, SOMAXCONN);

    SOCKET newConnection;
    for (size_t i = 0; i < 100; i++)
    {
        newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);

        if (newConnection == 0) {
            std::cout << "Connection Error!" << std::endl;
        }
        else {
            std::cout << "Client Connected!\n";
            char msg[256] = "Hello World!";
            send(newConnection, msg, sizeof(msg), NULL);

            Connection[i] = newConnection;
            Count++;

            CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, (LPVOID)(i), NULL, NULL);
        }
    }


    system("pause");
    return 0;
}