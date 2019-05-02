//---------------------------------------------------------
// gromero3.cc
//---------------------------------------------------------

#include <unistd.h>     // alarm
#include <atomic>       // atomic
#include <iostream>     // cout endl
#include <mutex>        // mutex
#include <thread>       // thread

using namespace std::chrono;

//---------------------------------------------------------

const int N = 32;
static_assert(N <= 64);

//---------------------------------------------------------

class barrera_t
{
public:
	void esperar(int yo)
	{
		unsigned long long _1 = 1ull << yo;
		bits |= _1;
		
		if (++count < N)
		{
			auto espera = 32us;
			while (bits & _1)
				std::this_thread::sleep_for(espera *= 2);
		}
		else
		{
			count = 0;
			bits = 0;
		}
	}

private:
	std::atomic<unsigned long long> bits;
	std::atomic<unsigned> count;
} barrera;

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

