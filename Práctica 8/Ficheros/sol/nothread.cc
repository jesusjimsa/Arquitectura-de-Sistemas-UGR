//-----------------------------------------------------------
// nothread.cc
//-----------------------------------------------------------

#include <unistd.h>
#include <csignal>
#include <iostream>

//-----------------------------------------------------------

void manejador_sigusr1(int)
{
	signal(SIGUSR1, manejador_sigusr1);
	std::cout << "[servidor]: petición recibida" << std::endl;
	std::cout << "[servidor]: respuesta enviada" << std::endl;
	raise(SIGUSR2);
}

//-----------------------------------------------------------

void manejador_sigusr2(int)
{
	signal(SIGUSR2, manejador_sigusr2);
	std::cout << "[cliente ]: respuesta recibida" << std::endl;
	std::cout << "[cliente ]: petición enviada" << std::endl;
	raise(SIGUSR1);
}

//-----------------------------------------------------------

int main()
{
	alarm(1);
	signal(SIGUSR1, manejador_sigusr1);
	signal(SIGUSR2, manejador_sigusr2);
	std::cout << "[cliente ]: petición enviada" << std::endl;
	raise(SIGUSR1);
}

//-----------------------------------------------------------

