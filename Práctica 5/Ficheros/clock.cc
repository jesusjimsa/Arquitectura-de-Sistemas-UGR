#include <iostream>
#include <chrono>

int main()
{
	using namespace std::chrono;
	
	auto start = high_resolution_clock::now();
	std::cout << "Hello World!" << std::endl;
	auto end = high_resolution_clock::now();

	std::cout << "Printing took "
	          << duration_cast<microseconds>(end - start).count()
	          << "µs" << std::endl;
}
