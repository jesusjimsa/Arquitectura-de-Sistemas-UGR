#include <iostream>
#include <chrono>

int main()
{
	using namespace std::chrono;
	
	auto start = high_resolution_clock::now();
	std::cout << "Hello World!" << std::endl;
	auto stop = high_resolution_clock::now();
	
	duration<double, std::micro> d = stop - start;
	
	std::cout << "Printing took "
	          << d.count()
	          << "µs" << std::endl;
}
