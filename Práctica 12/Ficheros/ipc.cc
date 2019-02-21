#include <chrono>
#include <iostream>
#include <thread>

const int N = 250;

int listo = 0;
int mensaje[N];

void productor()
{
	for (int i = 0; i < N; ++i)
	{
		mensaje[i % N] = 0x1234;
		listo = 1;
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

void consumidor()
{
	for (int i = 0; i < N; ++i)
	{
		while (!listo);
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
