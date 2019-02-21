//---------------------------------------------------------
// barrera.cc: esqueleto para completar
//---------------------------------------------------------

#include <unistd.h>  // alarm
#include <iostream>  // cout endl
#include <mutex>     // mutex
#include <thread>    // thread

//---------------------------------------------------------

const int N = 32;

//---------------------------------------------------------

class barrera_t
{
public:
	barrera_t(unsigned _limite) {}
	void esperar() {}
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

