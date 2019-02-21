//---------------------------------------------------------
// gromero2.cc
//---------------------------------------------------------

#include <unistd.h>     // alarm
#include <atomic>       // atomic
#include <bitset>       // bitset
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
	void esperar(int yo)
	{
		{
			std::unique_lock<std::shared_mutex> l(sm);
			bits.set(yo);
		}
		
		std::shared_lock<std::shared_mutex> l(sm);
		if (!bits.all())
		{
			cva.wait(l, [&]{ return !bits[yo]; });
		}
		else
		{
			bits.reset();
			cva.notify_all();
		}
	}

private:
	std::shared_mutex sm;
	std::condition_variable_any cva;
	std::bitset<N> bits;
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

