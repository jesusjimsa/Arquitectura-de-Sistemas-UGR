//-----------------------------------------------------------------------------
// struct.cc
//-----------------------------------------------------------------------------

#include <chrono>
#include <functional>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <random>
#include <typeinfo>

//-----------------------------------------------------------------------------

const int N = 10000, REP = 10000;

//-----------------------------------------------------------------------------

std::random_device device;
std::default_random_engine generator(device());
std::uniform_int_distribution<int> distribution(0, 9);
auto rng = std::bind(distribution, generator);

//-----------------------------------------------------------------------------

struct S 
{
	int a, b;
	S(): a(rng()), b(rng()) {}
} const s[N];

int R[REP + 1]; // because... for (int ii = 1; ii <= REP; ++ii)

//-----------------------------------------------------------------------------

void v0()
{
	for (int ii = 1; ii <= REP; ++ii)
	{
		int X1 = 0, X2 = 0;

		for(int i = 0; i < N; ++i)
			X1 += 2 * s[i].a + ii;

		for(int i = 0; i < N; ++i)
			X2 += 3 * s[i].b - ii;

		if (X1 <  X2)
			R[ii] = X1;
		else
			R[ii] = X2;
	}
}

//-----------------------------------------------------------------------------

template<class F> void test(F& f, const char* name)
{
	std::fill(R, R + REP, 0);

	for (int i = 0; i < 3; ++i)
		f();

	auto start = std::chrono::high_resolution_clock::now();
	f();
	auto stop = std::chrono::high_resolution_clock::now();

	std::cout << "function: " << name << "\t time: " << std::setw(7)
	          << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count()
	          << "us\t result = " <<  std::accumulate(R + 1, R + REP + 1, 0) << std::endl;
}

//-----------------------------------------------------------------------------

int main()
{
	test(v0, "v0");
}

//-----------------------------------------------------------------------------

