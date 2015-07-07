// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
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
	SOCKET socketClient = socket(AF_INET,SOCK_STREAM,0);
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr =inet_addr( "127.0.0.1");
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);
	connect(socketClient,(SOCKADDR *)&addrSrv,sizeof(SOCKADDR));
	char recvBuf[100];
	recv(socketClient,recvBuf,100,0);
	cout << recvBuf << endl;
	const char * str("this is from client");
	send(socketClient, "this is from client", strlen("this is from client") + 1, 0);
	closesocket(socketClient);
	WSACleanup();
	int tmp;
	cin >> tmp;
	return 0;
}

