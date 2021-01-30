// ClientC.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "stdafx.h"
#include <iostream>
#include <WinSock2.h>
//#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)

int main()
{    
    WSADATA wsaData;
    WORD DLLVersion = MAKEWORD(2, 1);

    if (WSAStartup(DLLVersion, &wsaData) != 0) {
        std::cout << "WSAStartup Error!\n";
        exit(1);
    }
    /*
    else{
        std::cout << "WSAStartup is Done!\n";
    }
    system("pause");
    system("cls");
    */

    SOCKADDR_IN addr;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(1111);
    addr.sin_family = AF_INET;

    SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL);
    if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
        std::cout << "Error: failed connect to Server!\n";
        return 1;
    }
    
    std::cout << "Connect for Server is Done!\n";
    char msg[256];
    recv(Connection, msg, sizeof(msg), NULL);

    std::cout << msg << std::endl;


    system("pause");
    return 0;
}