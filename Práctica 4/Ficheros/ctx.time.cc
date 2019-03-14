// from https://gist.github.com/teknoraver/822116c7b1ad616d6c3663e0508f6841
// ctx_time Copyright (C) 2018 Matteo Croce <mcroce@redhat.com>
// a tool measure the context switch time in nanoseconds

#include <unistd.h>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <limits>
#include <x86intrin.h>

int main()
{
	const unsigned N = 1000000;

	std::chrono::duration<long, std::nano> d[N];

	for (auto& i: d)
	{
		auto start = std::chrono::high_resolution_clock::now();
		syscall(-1L);
		i = std::chrono::high_resolution_clock::now() - start;
	}

	std::nth_element(d, d + N / 2, d + N);
	std::cout << "context switch time..." << std::endl
	          << "\tminimum: "
	          << std::min_element(d, d + N)->count() << "ns" << std::endl
	          << "\tmedian : "
	          << d[N / 2].count() << "ns" << std::endl;
}

