#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <algorithm>
#include <chrono>
#include <iostream>
#include <limits>

using namespace std;
using namespace std::chrono;

int main(int argc, char* argv[])
{
	const int n = 1000;
	duration<double, micro> rep[n];

	for (auto& r: rep)
	{
		high_resolution_clock::time_point start = high_resolution_clock::now();
		
		switch(fork())
		{
			case -1: cerr << argv[0] << ": error en fork" << endl; exit(EXIT_FAILURE);
			case 0:  execl("nulo", "nulo", NULL); break;
			default: wait(NULL); break;
		}
		
		high_resolution_clock::time_point stop = high_resolution_clock::now();
		
		r = (stop - start);
	}
	
	std::nth_element(rep, rep + n / 2, rep + n);
	
	cout << "crear y ejecutar un proceso nulo tarda: " << endl
	     << "mediana: " << rep[n/2].count() << " µs" << endl
	     << "minimo : " << min_element(rep, rep + n)->count() << " µs" << endl;
}

