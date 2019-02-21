#include <algorithm>
#include <chrono>
#include <iostream>
#include <thread>

using namespace std;
using namespace std::chrono;

int main(int argc, char* argv[])
{
	using namespace std;
	using namespace std::chrono;

	const int n = 1000;
	duration<double, micro> rep[n];

	for (auto& r: rep)
	{
		high_resolution_clock::time_point start = high_resolution_clock::now();

		thread t([]{});
		t.join();

		high_resolution_clock::time_point stop = high_resolution_clock::now();

		r = stop - start;
	}
	
	std::nth_element(rep, rep + n / 2, rep + n);
	
	cout << "crear y ejecutar una hebra nula tarda: " << endl
	     << "mediana: " << rep[n/2].count() << " µs" << endl
	     << "minimo : " << min_element(rep, rep + n)->count() << " µs" << endl;
}
