//-----------------------------------------------------------------------------
// pthread.cc
//-----------------------------------------------------------------------------

#include <pthread.h>  // pthread_barrier
#include <unistd.h>   // alarm
#include <iostream>   // cout endl
#include <mutex>      // mutex
#include <string>    // string
#include <thread>     // thread

//-----------------------------------------------------------------------------

const int N = 32;

//---------------------------------------------------------

pthread_barrier_t barrera;

//---------------------------------------------------------

void hebra(int yo)
{
	std::string   antes = std::to_string(yo) +   ": antes\n", 
	            despues = std::to_string(yo) + ": después\n";
	while(true)
	{
		std::cout << antes;
		pthread_barrier_wait(&barrera);
		std::cout << despues;
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

