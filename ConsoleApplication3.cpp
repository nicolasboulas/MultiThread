// ConsoleApplication3.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
//#include <iostream>
//#include <WS2tcpip.h>
//#include <thread>
#include "serveur.h"

//#pragma comment (lib, "ws2_32.lib")

using namespace std;


void main()
{
	serveur Leserveur;
	Leserveur.init();
	Leserveur.start();
}






/*
void main()
{
	WSADATA WSDATA;

	WORD ver = MAKEWORD(2, 2);

	int wsok = WSAStartup(ver, &WSDATA);
	if (wsok != 0)
	{
		std::cout << "Erreur WSAStratup" << std::endl;
		return;
	}

	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);

	if (listening == INVALID_SOCKET)
	{
		std::cout << "erreur Socket" << std::endl;
		return;
	}

	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(54888);
	hint.sin_addr.S_un.S_addr = INADDR_ANY;

	bind(listening, (sockaddr*)&hint, sizeof(hint));

	listen(listening, SOMAXCONN);

	sockaddr_in client;
	int clientsize = sizeof(client);

	SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientsize);



	while ((clientSocket = accept(listening, (sockaddr*)&client, &clientsize)) )
	{
		hProcessThread = CreateThread(NULL, 0, clientSocket, &p, 0, NULL);
	}





	char host[NI_MAXHOST];
	char service[NI_MAXHOST];


	ZeroMemory(host, NI_MAXHOST);
	ZeroMemory(service, NI_MAXHOST);

	if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
	{
		std::cout << host << "conecté sur le port " << service << endl;
	}
	else
	{
		inet_ntop(AF_INET, &client.sin_addr, host , NI_MAXHOST);
		std::cout << "connecté"; 
	}

	closesocket(listening);

	char buf[4096];

	while (true)
	{
		ZeroMemory(buf, 4096);

		int bytesReceived = recv(clientSocket, buf, 4096, 0);
		if (bytesReceived == SOCKET_ERROR)
		{
			std::cout << "erreur Donnée " << std::endl;
			break;
		}

		send(clientSocket, buf, bytesReceived + 1, 0);
	}





     
}

*/
