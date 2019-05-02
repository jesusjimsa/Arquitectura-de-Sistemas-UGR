//---------------------------------------------------------
// barrera_cv2.cc
//---------------------------------------------------------

#include <unistd.h>            // alarm
#include <atomic>              // atomic
#include <condition_variable>  // condition_variable
#include <iostream>            // cout endl
#include <mutex>               // mutex unique_lock
#include <string>              // string
#include <thread>              // thread

//---------------------------------------------------------

const int N = 32;

//---------------------------------------------------------

class barrera_t
{
public:
	explicit barrera_t(unsigned _limite): limite(_limite) {}

	void esperar()
	{
		std::unique_lock<std::mutex> lock(m);
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
	std::mutex m;
	std::condition_variable restart;
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

