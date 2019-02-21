//-----------------------------------------------------------
// fork.cc: busque una condición de carrera!!!
//-----------------------------------------------------------

#include <sys/wait.h>
#include <unistd.h>
#include <chrono>
#include <csignal>
#include <iostream>
#include <thread>

//-----------------------------------------------------------

using namespace std::chrono;

//-----------------------------------------------------------

pid_t servidor, cliente;

//-----------------------------------------------------------

void manejador_sigusr1(int)
{
	signal(SIGUSR1, manejador_sigusr1);
	std::cout << "[servidor]: petición recibida" << std::endl;
	std::cout << "[servidor]: respuesta enviada" << std::endl;
	kill(cliente, SIGUSR2);
}

//-----------------------------------------------------------

void manejador_sigusr2(int)
{
	signal(SIGUSR2, manejador_sigusr2);
	std::cout << "[cliente ]: respuesta recibida" << std::endl;
	std::cout << "[cliente ]: petición enviada" << std::endl;
	kill(servidor, SIGUSR1);
}

//-----------------------------------------------------------

int main()
{
	servidor = getpid();
	cliente = fork();
	
	switch(cliente)
	{
		case -1: exit(EXIT_FAILURE);
		         break;
		case  0: alarm(1);
		         signal(SIGUSR2, manejador_sigusr2);
		         std::cout << "[cliente ]: petición enviada" << std::endl;
		         kill(servidor, SIGUSR1);
		         std::this_thread::sleep_for(1s);
		         break;
		default: signal(SIGUSR1, manejador_sigusr1);
		         wait(nullptr);
		         break;
	}
}

//-----------------------------------------------------------

