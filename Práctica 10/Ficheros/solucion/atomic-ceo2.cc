//---------------------------------------------------------
// atomic-ceo2.cc
//---------------------------------------------------------

#include <unistd.h>  // alarm
#include <atomic>    // atomic
#include <iostream>  // cout endl
#include <mutex>     // mutex
#include <thread>    // thread

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
				std::this_thread::yield();
		}
	}

private:
	std::atomic<unsigned> en_espera[2], uso;
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

