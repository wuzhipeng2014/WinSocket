// ConsoleApplication5.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <WinSock2.h>
using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	WORD WSVersion = MAKEWORD(2, 2);
	WSAData wsData;
	int err;
	err = WSAStartup(WSVersion, &wsData);
	if (LOBYTE(wsData.wVersion) != 2 || HIBYTE(wsData.wVersion) != 2)
	{
		WSACleanup();
		return 0;
	}
	SOCKET socketServer = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in addSrv;
	addSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY); //htonl将ip地址转换为网络字节序
	addSrv.sin_family = AF_INET;
	addSrv.sin_port = htons(6000);                   //
	cout << "开始监听6000端口" << endl;
	bind(socketServer, (SOCKADDR *)&addSrv, sizeof(SOCKADDR));
	listen(socketServer, 5);
	SOCKADDR_IN addrClient;
	int len = sizeof(SOCKADDR);
	while (1)
	{
		SOCKET sockConn = accept(socketServer, (SOCKADDR *)&addrClient, &len);
		char sendBuffer[100];
		sprintf_s(sendBuffer, "welcome %s to my server ", inet_ntoa(addrClient.sin_addr));
		send(sockConn, sendBuffer, strlen(sendBuffer) + 1, 0);
		char receBuffer[100];
		recv(sockConn, receBuffer, 100, 0);
		cout << receBuffer << endl;
		closesocket(sockConn);
	}
	return 0;
}

