#include <chrono>
#include <iostream>
#include <thread>

using namespace std;

const int N = 250;

int listo = 0;
int mensaje[N];

void productor()
{
	for (int i = 0; i < N; ++i)
	{
		mensaje[i % N] = 0x1234;
		listo = 1;
		std::this_thread::sleep_for(1ms);
	}
}

void consumidor()
{
	for (int i = 0; i < N; ++i)
	{
		while (listo == 0);
		listo = 0;
		std::cout << mensaje[i] << ' ';
	}
}

int main()
{
	std::thread p(productor), c(consumidor);
	p.join();
	c.join();
}
