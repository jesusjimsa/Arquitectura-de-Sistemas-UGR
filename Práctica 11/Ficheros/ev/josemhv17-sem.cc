//---------------------------------------------------------
// le-sem.cc
//---------------------------------------------------------

#include <semaphore.h>

#include <atomic>
#include <chrono>
#include <iostream>
#include <random>
#include <thread>

//---------------------------------------------------------

using namespace std;

//---------------------------------------------------------

atomic<bool> run(true);

sem_t leer,escribir;

atomic<int> contador(0);

//---------------------------------------------------------

void seccion_critica(char c)
{
	for (char i = 0; i < 10; ++i)
		cout << c++;
	cout << endl;
}

//---------------------------------------------------------

void lector()
{
	while (run)
	{
		sem_wait(&leer);
		contador = contador + 1;
		if(contador==1)
			sem_wait(&escribir);
		sem_post(&leer);
		
		seccion_critica('0');
		
		sem_wait(&leer);
		contador = contador - 1;
		if(contador==0)
			sem_post(&escribir);
		sem_post(&leer);
	}
}

//---------------------------------------------------------

void escritor()
{
	while (run)
	{
		sem_wait(&escribir);
		seccion_critica('a');
		sem_post(&escribir);
	}
}

//---------------------------------------------------------

int main()
{
	const unsigned N = 8;
	thread lectores[N], escritores[N];
	std::default_random_engine engine;
	
	sem_init(&leer,0,1);
	sem_init(&escribir,0,1);
	
	for (unsigned i = 0; i < N; ++i)
		if (engine() & 1)
		{
			  lectores[i] = thread(  lector);
			escritores[i] = thread(escritor);
		}
		else
		{
			escritores[i] = thread(escritor);
			  lectores[i] = thread(  lector);
		}
	
	this_thread::sleep_for(chrono::seconds(1));
	run = false;
	
	for(thread& i:   lectores) i.join();
	for(thread& i: escritores) i.join();
}

//---------------------------------------------------------
