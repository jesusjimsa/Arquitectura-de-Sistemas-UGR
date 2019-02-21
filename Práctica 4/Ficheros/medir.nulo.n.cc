//---------------------------------------------------------
// medir.nulo.n.cc
//---------------------------------------------------------

#include <sys/wait.h>
#include <unistd.h>

#include <chrono>
#include <iomanip>
#include <iostream>

//---------------------------------------------------------

int main()
{
	const unsigned N = 1000;
	
	auto start = std::chrono::high_resolution_clock::now();
	for (unsigned i = 0; i < N; ++i)
		switch(fork())
		{
			case -1: std::cout << "fallo en fork()!"; exit(EXIT_FAILURE); break;
			case 0:  execl("./nulo", "./nulo", nullptr); break;
			default: int r; wait(&r); break;
		}
	auto stop = std::chrono::high_resolution_clock::now();
	
	std::chrono::duration<double, std::milli> d = stop - start;
	std::cout << "la ejecución del proceso nulo tarda en media: "
	          << std::fixed << std::setprecision(2)
	          << d.count() / N << "ms" << std::endl;
}

//---------------------------------------------------------

