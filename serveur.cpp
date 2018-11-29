#include "pch.h"
#include "serveur.h"

serveur::serveur()
{
	running = false;
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




	sockaddr_in l_client;
	int clientsize;
	//SOCKET clientSocket;
	
	listening = socket(AF_INET, SOCK_STREAM, 0);
	
	if (listening == INVALID_SOCKET)
	{
		std::cout << "erreur Socket" << std::endl;
		return 1;
	}


	bind(listening, (sockaddr*)&hint, sizeof(hint));

	listen(listening, SOMAXCONN);

	running = true;
	
	fd_set master;
	FD_ZERO(&master);

	FD_SET(listening, &master);

	clientsize = sizeof(l_client);

	while (running)
	{
		fd_set copy = master;
		int socketCount = select(0, &copy, nullptr, nullptr, nullptr);
		
		for (int i = 0; i < socketCount; i++)
		{
			SOCKET sock = copy.fd_array[i];
			if (sock == listening)
			{
				SOCKET client = accept(listening, (sockaddr*)&l_client, &clientsize);

				

				

				FD_SET(client, &master);

				char host[NI_MAXHOST];
				char service[NI_MAXHOST];



				ZeroMemory(host, NI_MAXHOST);
				ZeroMemory(service, NI_MAXHOST);

				getnameinfo((sockaddr*)&l_client, sizeof(l_client), host, NI_MAXHOST, service, NI_MAXSERV, 0);

				std::cout << host << " est connecte sur le port " << service << std::endl;

				send(client, "salut le client ", 20, 0);
			}
			else
			{
				char buf[4096];
				ZeroMemory(buf, 4096);

				int bytesIn = recv(sock, buf, 4096, 0);

				if (bytesIn <= 0)
				{
					closesocket(sock);
					FD_CLR(sock, &master);
				}
				else
				{
					for (int i = 0; i < master.fd_count; i++)
					{
						SOCKET outSock = master.fd_array[i];
						if (outSock != listening && outSock != sock)
						{
							send(outSock, buf, bytesIn, 0);
						}
					}
				}
			}
		}
	}

	


	return 0;
}


int serveur::pause()
{
	running = false;
	closesocket(listening);
	return 0;
}

