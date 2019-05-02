//---------------------------------------------------------
// gromero.cc
//---------------------------------------------------------

#include <unistd.h>     // alarm
#include <atomic>       // atomic
#include <chrono>       // us
#include <iostream>     // cout endl
#include <shared_mutex> // shared_mutex
#include <thread>       // thread

using namespace std::chrono;

//---------------------------------------------------------

const int N = 32;

//---------------------------------------------------------

class barrera_t
{
public:
	explicit barrera_t(unsigned _limite): 
		generacion(0), limite(_limite), contador(0) {}
	
	void esperar()
	{
		sm.lock_shared();
		unsigned mi_generacion = generacion;
		sm.unlock_shared();
		
		if (++contador < limite)
		{
			auto espera = 64us;
			while (mi_generacion == generacion)
				std::this_thread::sleep_for(espera *= 2);
		}
		else
		{
			contador = 0;
			std::unique_lock<std::shared_mutex> l(sm);
			++generacion;
		}
	}

private:
	std::shared_mutex sm;
	unsigned generacion, limite;
	std::atomic<unsigned> contador;
} barrera(N);

//---------------------------------------------------------

void hebra(int yo)
{
	std::string   antes = std::to_string(yo) +   ": antes\n", 
	            despues = std::to_string(yo) + ": después\n";
	while(true)
	{
		std::cout << antes;
		barrera.esperar();
		std::cout << despues;
	}
}

//---------------------------------------------------------

int main()
{
	alarm(1);
	std::thread t[N];
	for (int i = 0; i < N; ++i) t[i] = std::thread(hebra, i);
	for (auto& i: t) i.join();
}

//---------------------------------------------------------

