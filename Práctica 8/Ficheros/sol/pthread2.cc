//-------------------------------------------------
// pthread2.cc
//-------------------------------------------------

#include <pthread.h> // pthread_create pthread_join
#include <unistd.h>  // alarm sleep
#include <csignal>   // signal SIGALRM
#include <iostream>  // endl cout 

//-------------------------------------------------

pthread_t id_cliente, id_servidor;

//-------------------------------------------------

void manejador_sigusr2(int)
{
	signal(SIGUSR2, manejador_sigusr2);
	std::cout << "[cliente ]: respuesta recibida" << std::endl;
	std::cout << "[cliente ]: petición enviada" << std::endl;
	pthread_kill(id_servidor, SIGUSR1);
}

void *hebra_cliente(void*)
{
	signal(SIGUSR2, manejador_sigusr2);
	std::cout << "[cliente ]: petición enviada" << std::endl;
	pthread_kill(id_servidor, SIGUSR1);
	sleep(1);
	return NULL;
}

//-------------------------------------------------

void manejador_sigusr1(int)
{
	signal(SIGUSR1, manejador_sigusr1);
	std::cout << "[servidor]: petición recibida" << std::endl;
	std::cout << "[servidor]: respuesta enviada" << std::endl;
	pthread_kill(id_servidor, SIGUSR2);
}

void *hebra_servidor(void*)
{
	signal(SIGUSR1, manejador_sigusr1);
	pthread_create(&id_cliente , NULL, hebra_cliente , NULL);
	pthread_join(id_cliente , NULL);
	return NULL;
}

//-------------------------------------------------

int main()
{
	alarm(1);
	pthread_create(&id_servidor, NULL, hebra_servidor, NULL);
	pthread_join(id_servidor, NULL);
}

//-------------------------------------------------

