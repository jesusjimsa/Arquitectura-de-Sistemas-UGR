#include <algorithm>
#include <parallel/algorithm>
#include <cassert>
#include <chrono>
#include <functional>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

const int W = 22;

std::vector<int> original, sorted, tmp;

void f1()
{
	std::sort(tmp.begin(), tmp.end());
}

void f2()
{
	std::stable_sort(tmp.begin(), tmp.end());
}

void f3()
{
	std::__parallel::sort(tmp.begin(), tmp.end());
}

void f4()
{
	std::__parallel::stable_sort(tmp.begin(), tmp.end());
}

template<typename F> void test(F f)
{
	const int R = 100;
	std::chrono::duration<long long, std::nano> rep[R];

	for (auto& r: rep)
	{
		tmp = original;
		auto start = std::chrono::high_resolution_clock::now();
		f();
		auto stop = std::chrono::high_resolution_clock::now();
		r = stop - start;
	}
	assert(tmp == sorted);
	std::nth_element(rep, rep + R, rep + R/2);
	std::cout << std::setw(W) << rep[R/2].count();
}

int main()
{
	std::cout << std::setw(W/2) << "size" 
	          << std::setw(W) << "sort"
	          << std::setw(W) << "stable_sort"
	          << std::setw(W) << "parallel::sort"
	          << std::setw(W) << "parallel::stable_sort" << std::endl;
	
	for (int i = 1; i <= (1<<20); i <<= 1)
	{

		original = sorted = tmp = std::vector<int>(i);
	
		std::random_device r;
		std::default_random_engine e(r());
		std::uniform_int_distribution<int> d(0, i);
		auto rng = std::bind(d, e);
	
		std::generate(original.begin(), original.end(), rng);
		sorted = original;
		std::sort(sorted.begin(), sorted.end());
		
		std::cout << std::setw(W/2) << i;
		
		test(f1);
		test(f2);
		test(f3);
		test(f4);

		std::cout << std::endl;
	}
}
