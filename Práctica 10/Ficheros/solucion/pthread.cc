//-----------------------------------------------------------------------------
// pthread.cc
//-----------------------------------------------------------------------------

#include <pthread.h>  // pthread_barrier
#include <unistd.h>   // alarm
#include <iostream>   // cout endl
#include <mutex>      // mutex
#include <thread>     // thread

//-----------------------------------------------------------------------------

const int N = 32;

//---------------------------------------------------------

pthread_barrier_t barrera;

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
		pthread_barrier_wait(&barrera);
		msg(yo, "después");
	}
}

//---------------------------------------------------------

int main()
{
	alarm(1);
	pthread_barrier_init(&barrera, NULL, N);
	std::thread t[N];
	for (int i = 0; i < N; ++i) t[i] = std::thread(hebra, i);
	for (auto& i: t) i.join();
}

//---------------------------------------------------------

