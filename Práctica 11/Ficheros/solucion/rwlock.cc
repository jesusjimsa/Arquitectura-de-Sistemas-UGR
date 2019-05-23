//---------------------------------------------------------
// rwlock.cc // solución de pthread
//---------------------------------------------------------

#include <pthread.h>
#include <atomic>
#include <chrono>
#include <iostream>
#include <mutex>
#include <random>
#include <thread>

//---------------------------------------------------------

using namespace std;

//---------------------------------------------------------

atomic<bool> run(true);
pthread_rwlock_t rwlock;  // cerrojo de lectura/escritura

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
		pthread_rwlock_rdlock(&rwlock);
		seccion_critica('0');
		pthread_rwlock_unlock(&rwlock);
	}
}

//---------------------------------------------------------

void escritor()
{
	while (run)
	{
		pthread_rwlock_wrlock(&rwlock);
		seccion_critica('a');
		pthread_rwlock_unlock(&rwlock); 
	}
}

//---------------------------------------------------------

int main()
{
	const unsigned N = 8;
	thread lectores[N], escritores[N];
	std::default_random_engine engine;
	
	pthread_rwlock_init(&rwlock, NULL);
	
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
