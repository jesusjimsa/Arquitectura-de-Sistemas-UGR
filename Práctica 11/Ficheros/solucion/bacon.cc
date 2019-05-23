//---------------------------------------------------------
// bacon.cc: prioridad a los escritores
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

//---------------------------------------------------------

class rwlock_t
{
public:
	rwlock_t(): ar(0), rr(0), aw(0), ww(0)
	{
		sem_init(&R     , 0, 0);
		sem_init(&W     , 0, 0);
		sem_init(&WGUARD, 0, 1);
		sem_init(&CGUARD, 0, 1);
	}
	
	void reader_lock()
	{
		sem_wait(&CGUARD);
		ar = ar + 1;
		if (aw == 0)
		{
			rr = rr + 1;
			sem_post(&R);
		}
		sem_post(&CGUARD);
		sem_wait(&R);
	}
	
	void reader_unlock()
	{
		sem_wait(&CGUARD);
		rr = rr - 1;
		ar = ar - 1;
		if (rr == 0)
			while (ww < aw)
			{
				ww = ww + 1;
				sem_post(&W);
			}
		sem_post(&CGUARD);
	}
	
	void writer_lock()
	{
		sem_wait(&CGUARD);
		aw = aw + 1;
		if (rr == 0)
		{
			ww = ww + 1;
			sem_post(&W);
		}
		sem_post(&CGUARD);
		sem_wait(&W);
		sem_wait(&WGUARD);
	}
	
	void writer_unlock()
	{
		sem_post(&WGUARD);
		sem_wait(&CGUARD);
		ww = ww - 1;
		aw = aw - 1;
		if (aw == 0)
			while (rr < ar)
			{
				rr = rr + 1;
				sem_post(&R);
			}
		sem_post(&CGUARD);
	}
	
private:
	sem_t R,      // lecturas pendientes
	      W,      // escrituras pendientes
	      WGUARD, // escritura exclusiva
	      CGUARD; // exclusión contadores
	int ar,       // lectores activos
	    rr,       // lectores leyendo
	    aw,       // escritores activos
	    ww;       // escritores escribiendo 
} rwlock;

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
		rwlock.reader_lock();
		seccion_critica('0');
		rwlock.reader_unlock();
	}
}

//---------------------------------------------------------

void escritor()
{
	while (run)
	{
		rwlock.writer_lock();
		seccion_critica('a');
		rwlock.writer_unlock();
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
