//-----------------------------------------------------------
// thread.cc
//-----------------------------------------------------------

#include <pthread.h>
#include <unistd.h>
#include <chrono>
#include <csignal>
#include <iostream>
#include <thread>

//-----------------------------------------------------------

using namespace std::chrono_literals;

//-----------------------------------------------------------

std::thread cliente, servidor;

//-----------------------------------------------------------

void manejador_sigusr1(int)
{
	signal(SIGUSR1, manejador_sigusr1);
	std::cout << "[servidor]: petición recibida" << std::endl;
	std::cout << "[servidor]: respuesta enviada" << std::endl;
	pthread_kill(cliente.native_handle(), SIGUSR2);
}

//-----------------------------------------------------------

void manejador_sigusr2(int)
{
	signal(SIGUSR2, manejador_sigusr2);
	std::cout << "[cliente ]: respuesta recibida" << std::endl;
	std::cout << "[cliente ]: petición enviada" << std::endl;
	pthread_kill(servidor.native_handle(), SIGUSR1);
}

//-----------------------------------------------------------

int main()
{
	alarm(1);
	
	servidor = std::thread([]
	{
		signal(SIGUSR1, manejador_sigusr1);
		cliente = std::thread([]
		{
			signal(SIGUSR2, manejador_sigusr2);
			std::cout << "[cliente ]: petición enviada" << std::endl;
			pthread_kill(servidor.native_handle(), SIGUSR1);
			std::this_thread::sleep_for(1s);
		});
		cliente.join();
	});
	servidor.join();
}

//-----------------------------------------------------------

