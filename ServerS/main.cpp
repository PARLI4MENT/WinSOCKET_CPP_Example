// ServerS.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "stdafx.h"
#include <iostream>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

#pragma warning(disable: 4996)

int main(int args, char* argv[])
{
    WSADATA wsaData;
    WORD DLLVersion = MAKEWORD(2, 1);
    if (WSAStartup(DLLVersion, &wsaData) != 0){
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
    newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);
    //newConnection = accept(sListen, (SOCKADDR*)&addr, (int*)sizeof(addr));

    if (newConnection == 0){
        std::cout << "Connection Error!" << std::endl;
    }
    else{
        std::cout << "Client Connected!\n";
        char msg[256] = "Hello World!";
        send(newConnection, msg, sizeof(msg), NULL);
    }


    system("pause");
    return 0;
}