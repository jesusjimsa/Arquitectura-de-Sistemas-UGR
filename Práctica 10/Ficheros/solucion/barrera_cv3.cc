//---------------------------------------------------------
// barrera_cv3.cc
//---------------------------------------------------------

#include <unistd.h>            // alarm
#include <condition_variable>  // condition_variable
#include <iostream>
#include <mutex>               // mutex
#include <string>              // string
#include <thread>

//---------------------------------------------------------

const int N = 7;

//---------------------------------------------------------

class barrera_t
{
public:
	barrera_t(unsigned _limite): 
		contador(_limite), generacion(0), limite(_limite) {}

	void esperar()
	{
		std::unique_lock<std::mutex> lock(mutex);
		unsigned copia = generacion;
		if (--contador == 0)
		{
			++generacion;
			contador = limite;
			bloqueadas.notify_all();
		}
		else
		{
			bloqueadas.wait(lock, [&]{ return copia != generacion; });
		}
	}

private:
	std::mutex mutex;
	std::condition_variable bloqueadas;
	unsigned contador, generacion, limite;
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

