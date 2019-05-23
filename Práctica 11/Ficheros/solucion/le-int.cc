//---------------------------------------------------------
// le-int.cc // interruptor --> inanición
//---------------------------------------------------------

#include <atomic>
#include <chrono>
#include <iostream>
#include <mutex>
#include <random>
#include <thread>
#include "interruptor.h"

//---------------------------------------------------------

using namespace std;

//---------------------------------------------------------

atomic<bool> run(true);
interruptor i;
mutex em;               // exclusión mutua

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
		i.lock(em);
		seccion_critica('0');
		i.unlock(em);
	}
}

//---------------------------------------------------------

void escritor()
{
	while (run)
	{
		em.lock();
		seccion_critica('a');
		em.unlock();
	}
}

//---------------------------------------------------------

int main()
{
	const unsigned N = 8;
	thread lectores[N], escritores[N];
	std::default_random_engine engine;
	
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
	
	this_thread::sleep_for(1s);
	run = false;
	
	for(thread& i:   lectores) i.join();
	for(thread& i: escritores) i.join();
}

//---------------------------------------------------------
