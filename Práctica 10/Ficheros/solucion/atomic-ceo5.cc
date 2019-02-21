//---------------------------------------------------------
// atomic-ceo5.cc
//---------------------------------------------------------

#include <unistd.h>  // alarm 
#include <atomic>    // atomic
#include <chrono>    // us
#include <iostream>  // cout endl
#include <mutex>     // mutex
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
