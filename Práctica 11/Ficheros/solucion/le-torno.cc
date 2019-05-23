//---------------------------------------------------------
// le-torno.cc // interruptor + torno = libre de inanición
//---------------------------------------------------------

#include <atomic>
#include <iostream>
#include <random>
#include <thread>
#include "interruptor.h"

//---------------------------------------------------------

using namespace std;

//---------------------------------------------------------

atomic<bool> run(true);
interruptor i;
mutex nadie, torno;

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
		torno.lock();
		torno.unlock();
		i.lock(nadie);
		seccion_critica('0');
		i.unlock(nadie);
	}
}

//---------------------------------------------------------

void escritor()
{
	while (run)
	{
		torno.lock();
		nadie.lock();
		seccion_critica('a');
		torno.unlock();
		nadie.unlock();
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
