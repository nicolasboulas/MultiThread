#include "pch.h"
#include "serveur.h"

serveur::serveur()
{
	running = false;
}

DWORD WINAPI mythread(void* arg)
{
	std::cout << "cest connecte" << std::endl;
	return 0;
}

int serveur::init()
{
	WSADATA WSDATA;

	WORD ver = MAKEWORD(2, 2);

	int wsok = WSAStartup(ver, &WSDATA);
	if (wsok != 0)
	{
		std::cout << "Erreur WSAStratup" << std::endl;
		return 1;
	}

	hint.sin_family = AF_INET;
	hint.sin_port = htons(54888);
	hint.sin_addr.S_un.S_addr = INADDR_ANY;
}

int serveur::start()
{
	HANDLE hProcessthread;
	struct thread_param p;
	std::thread thread[3];




	sockaddr_in client;
	int clientsize;
	SOCKET clientSocket;
	
	listening = socket(AF_INET, SOCK_STREAM, 0);
	
	if (listening == INVALID_SOCKET)
	{
		std::cout << "erreur Socket" << std::endl;
		return 1;
	}


	bind(listening, (sockaddr*)&hint, sizeof(hint));

	listen(listening, SOMAXCONN);

	running = true;
	clientsize = sizeof(client);

	while (running)
	{
		clientSocket = accept(listening, (sockaddr*)&client, &clientsize);
		char host[NI_MAXHOST];
		char service[NI_MAXHOST];

	

		ZeroMemory(host, NI_MAXHOST);
		ZeroMemory(service, NI_MAXHOST);

		std::cout << "connecte sur le port " << service << std::endl;

		if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
		{
			std::cout << host << "conecté sur le port " << service << std::endl;
		}
		else
		{
			inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
			std::cout << "connecté";
		}

		p.ser = this;
		p.soc = clientSocket;
	}

	

	//hProcessthread = CreateThread(NULL, 0, &serveur::ThreadLauncher, &p, 0, NULL);

	//hProcessthread = CreateThread(NULL, 0, &mythread, (LPVOID)this, 0, NULL);


	return 0;
}


int serveur::pause()
{
	running = false;
	closesocket(listening);
	return 0;
}

