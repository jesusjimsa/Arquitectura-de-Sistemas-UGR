// from: https://gist.github.com/teknoraver/ebee75c5bc4eb8533b8e761d0e57b7d9
// ctx_clock Copyright (C) 2018 Matteo Croce <mcroce@redhat.com>
// a tool measure the context switch time in clock cycles

#include <unistd.h>
#include <iostream>
#include <limits>
#include <x86intrin.h>

int main()
{
	unsigned junk;
	unsigned long long cycles = std::numeric_limits<unsigned long long>::max();

	for (int i = 0; i < 10000000; ++i)
	{
		auto start = __rdtscp(&junk);
		syscall(-1L);
		cycles = std::min(cycles, __rdtscp(&junk) - start);
	}

	std::cout << "context switch: " << cycles << " cycles" << std::endl;
}

