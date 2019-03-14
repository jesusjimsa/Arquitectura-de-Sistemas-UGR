//---------------------------------------------------------
// medir.nulo.n.cc
//---------------------------------------------------------

#include <sys/wait.h>
#include <unistd.h>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>

int main()
{
	const unsigned N = 1000;
	std::chrono::duration<double, std::milli> d[N];

	for (auto& i: d)
	{
		auto start = std::chrono::high_resolution_clock::now();
		switch(fork())
		{
			case -1: std::cout << "fallo en fork()!"; exit(EXIT_FAILURE); break;
			case  0: execl("./nulo", "./nulo", nullptr); break;
			default: wait(nullptr); break;
		}
		i = std::chrono::high_resolution_clock::now() - start;
	}

	std::nth_element(d, d + N / 2, d + N);
	std::cout << "la ejecución del proceso nulo tarda..." << std::endl
	          << "\tmínimo : " << std::fixed << std::setprecision(2)
	          << std::min_element(d, d + N)->count() << "ms" << std::endl
	          << "\tmediana: " << std::fixed << std::setprecision(2)
	          << d[N / 2].count() << "ms" << std::endl;
}

