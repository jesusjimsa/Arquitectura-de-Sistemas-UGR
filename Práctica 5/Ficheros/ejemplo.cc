#include <iostream>
#include <thread>

void hebra()
{
	std::cout << "[2] hola: " 
	          << std::this_thread::get_id() 
	          << std::endl;
}

int main()
{
	std::cout << "[1] hola: " 
	          << std::this_thread::get_id() 
	          << std::endl;
	std::thread t(hebra);
	t.join();
}
