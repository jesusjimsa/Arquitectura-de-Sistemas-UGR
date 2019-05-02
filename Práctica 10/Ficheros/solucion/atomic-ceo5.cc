//---------------------------------------------------------
// atomic-ceo5.cc
//---------------------------------------------------------

#include <unistd.h>  // alarm 
#include <atomic>    // atomic
#include <chrono>    // us
#include <iostream>  // cout endl
#include <mutex>     // mutex
#include <string>    // string
#include <thread>    // thread

//---------------------------------------------------------

const int N = 32;

//---------------------------------------------------------

class barrera_t
{
public:
	explicit barrera_t(unsigned l): limite(l) {}

	void esperar()
	{
		unsigned mi_ciclo = ciclo;
		if (++en_espera == limite)
		{
			en_espera = 0;
			++ciclo;
		}
		else
		{
			using namespace std::chrono;
			auto espera = 128us;
			while(ciclo == mi_ciclo)
				std::this_thread::sleep_for(espera *= 2);
		}
	}

private:
	std::atomic<unsigned> ciclo, en_espera;
	unsigned limite;
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
