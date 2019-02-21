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

void msg(int yo, const char *txt)
{
	static std::mutex m;
	std::unique_lock<std::mutex> l(m);
	std::cout << yo << ": " << txt << std::endl;
}

//---------------------------------------------------------

void hebra(int yo)
{
	while(true)
	{
		msg(yo, "antes");
		barrera.esperar();
		msg(yo, "después");
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

