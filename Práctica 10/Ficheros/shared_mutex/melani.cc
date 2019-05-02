//---------------------------------------------------------
// melani.cc
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
		en_espera{0, 0}, uso(0), limite(_limite) {}

	void esperar()
	{
		std::unique_lock<std::shared_mutex> lock(m);
		unsigned uso_local = uso;
		if (++en_espera[uso_local] < limite)
		{
			restart.wait(lock, [&]{ return en_espera[uso_local] == 0; });
		}
		else
		{
			uso = 1 - uso;
			en_espera[uso_local] = 0;
			restart.notify_all();
		}
	}

private:
	std::atomic<unsigned> en_espera[2], uso;
	unsigned limite;
	std::shared_mutex m;
	std::condition_variable_any restart;
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

