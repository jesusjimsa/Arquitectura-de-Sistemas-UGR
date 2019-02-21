//---------------------------------------------------------
// barrera_cv3.cc
//---------------------------------------------------------

#include <unistd.h>            // alarm
#include <condition_variable>  // condition_variable
#include <iostream>
#include <mutex>               // mutex
#include <thread>

//---------------------------------------------------------

const int N = 32;

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

