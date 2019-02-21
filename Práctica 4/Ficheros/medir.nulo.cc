//---------------------------------------------------------
// medir.nulo.cc
//---------------------------------------------------------

#include <sys/wait.h>
#include <unistd.h>

#include <chrono>
#include <iostream>

//---------------------------------------------------------

int main()
{
	using namespace std::chrono;
	
	auto start = high_resolution_clock::now();
	switch(fork())
	{
		case -1: std::cout << "fallo en fork()!"; break;
		case 0:  execl("./nulo", "./nulo", nullptr); break;
		default: int r; wait(&r); break;
	}
	auto stop = high_resolution_clock::now();
	std::cout << "la ejecución del proceso nulo tarda "
	          << duration_cast<nanoseconds>(stop - start).count()
	          << " ns" << std::endl;
}

//---------------------------------------------------------

