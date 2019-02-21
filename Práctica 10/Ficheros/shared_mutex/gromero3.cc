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
		barrera.esperar(yo);
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

