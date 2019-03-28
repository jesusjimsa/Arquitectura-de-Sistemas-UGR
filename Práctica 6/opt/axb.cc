#include <algorithm>
#include <chrono>
#include <functional>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <numeric>
#include <random>
#include <typeinfo>

//-----------------------------------------------------------------------------

const int M = 1234, N = 5678; // multiplos de 2 por quitar if y desenrollar

static_assert(M % 2 == 0 && N % 2 == 0);

//-----------------------------------------------------------------------------

int a[N][M], b[N][M], c[N];

//-----------------------------------------------------------------------------

void reset()
{
	static std::random_device device;
	static std::default_random_engine generator(device());
	std::uniform_int_distribution<int> distribution(-5, 5);
	auto rng = std::bind(distribution, generator);
	
	for (int i = 0; i < N; ++i)
	{
		c[i] = 0;
		for (int j = 0; j < M; ++j)
		{
			a[i][j] = rng();
			b[i][j] = rng();
		}
	}
}

//-----------------------------------------------------------------------------

void f0() // original
{
	for (int i = 0; i < M; ++i)
		for (int j = 0; j < N; ++j)
			if ((j % 2) == 0)
				c[j] += a[j][i] + b[j][i];
			else
				c[j] += a[j][i] - b[j][i];
}

//-----------------------------------------------------------------------------

template<class F> void test(const F& f, const char* name)
{
	reset();
	
	for (int i = 0; i < 3; ++i)
		f();
	
	const unsigned REP = 25;
	std::chrono::duration<double, std::milli> rep[REP];
	for (auto& i: rep)
	{
		auto start = std::chrono::high_resolution_clock::now();
		f();
		auto stop = std::chrono::high_resolution_clock::now();
		i = stop - start;
	}
	
	std::nth_element(std::begin(rep), std::begin(rep) + REP / 2, std::end(rep));
	std::cout << std::setw(25) << name << ':'
	          << "  time: " << std::fixed << std::setprecision(3) << std::setw(7)
	          << rep[REP / 2].count() << "ms"
	          << "  result = " <<  std::accumulate(std::begin(c), std::end(c), 0) 
	          << std::endl;
}

//-----------------------------------------------------------------------------

int main()
{
	test(f0, "original");
}

//-----------------------------------------------------------------------------

