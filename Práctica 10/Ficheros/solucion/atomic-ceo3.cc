//---------------------------------------------------------
// atomic-ceo3.cc
//---------------------------------------------------------

#include <unistd.h>  // alarm
#include <atomic>
#include <chrono>
#include <iostream>  // cout endl
#include <mutex>     // mutex
#include <string>    // string
#include <thread>    // thread

using namespace std::chrono;

//---------------------------------------------------------

const int N = 32;

//---------------------------------------------------------

class barrera_t
{
public:
	explicit barrera_t(unsigned _limite): limite(_limite) {}

	void esperar()
	{
		unsigned uso_local = uso;

		++en_espera[uso_local];

		if (en_espera[uso_local] == limite)
		{
			uso = 1 - uso;
			en_espera[uso_local] = 0;
		}
		else
		{
			while(en_espera[uso_local] > 0)
				std::this_thread::sleep_for(256ns);
		}
	}

private:
	std::atomic<unsigned> en_espera[2], uso;
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

