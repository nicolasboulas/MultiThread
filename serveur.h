#pragma once

#include "pch.h"
#include <iostream>
#include <WS2tcpip.h>
#include <thread>
//#include "ThreadParam.h"

#pragma comment (lib, "ws2_32.lib")

class serveur;



struct thread_param
{
	serveur* ser;
	SOCKET soc;
};


class serveur 
{
private :
	SOCKET listening;
	//int port;
	sockaddr_in hint;
	bool running;
	DWORD ClientThread(SOCKET);

public :
	serveur();
	int init();
	int start();
	int pause();
	static DWORD WINAPI ThreadLauncher(void *p) 
	{
		struct thread_param *Obj = reinterpret_cast<struct thread_param*>(p);
		serveur *s = Obj->ser;
		return s->ClientThread(Obj->soc);
	}
};