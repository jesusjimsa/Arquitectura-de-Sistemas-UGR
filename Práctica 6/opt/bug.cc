//-----------------------------------------------------------------------------

#include <cassert>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>
#include "demangle.h"

//-----------------------------------------------------------------------------

template<class T> T fib(T n)
{
	static std::vector<T> solutions = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34};
	
	std::size_t last = solutions.size();
	
	if (!(n < last))
	{
		solutions.resize(n + 1);
		for (auto i = solutions.begin() + last; i != solutions.end(); ++i)
			*i = *(i - 2) + *(i - 1);
	}
	
	return solutions[n];
}

//-----------------------------------------------------------------------------

template<typename T> void test()
{
	T i;
	
	for (i = 0; i < std::numeric_limits<T>::max() - 1; ++i)
		if (fib(i) > fib(i + 1))
			break;
	
	std::cout.imbue(std::locale("es_ES"));
	
	std::cout << ec::demangle(i) << ":" << std::endl;
	for (T j = i - 1; j < i + 2; ++j)
		std::cout << "\t f(" << j << ") = " 
		          << std::setw(26) << fib(j) << std::endl;
}

//-----------------------------------------------------------------------------

int main()
{
	test<               int>();
	test<          unsigned>();
	test<              long>();
	test<     unsigned long>();
	test<         long long>();
	test<unsigned long long>();
}

//-----------------------------------------------------------------------------
