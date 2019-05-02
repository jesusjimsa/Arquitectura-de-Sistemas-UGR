//---------------------------------------------------------
// jmherrera.cc
//---------------------------------------------------------

#include <unistd.h>     // alarm
#include <atomic>       // atomic
#include <chrono>       // us
#include <iostream>     // cout endl
#include <shared_mutex> // shared_mutex
#include <thread>       // thread

//---------------------------------------------------------

const int N = 32;

//---------------------------------------------------------

class barrera_t
{
public:
	barrera_t(unsigned _limite): en_espera{0, 0}, uso(0), limite(_limite) {}

	void esperar()
	{
		unsigned uso_local = uso;
		
		//shared_lock<shared_mutex> lock(m);
		++en_espera[uso_local];
		
		if (en_espera[uso_local] == limite)
		{
			uso = 1 - uso;
			en_espera[uso_local] = 0;
		}
		else
		{
			using namespace std::chrono;
			auto espera = 64us;
			while (en_espera[uso_local] > 0)
				std::this_thread::sleep_for(espera *= 2);
		}
	}

private:
	std::atomic<unsigned> en_espera[2], uso;
	unsigned limite;
//	std::shared_mutex m;
	
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

