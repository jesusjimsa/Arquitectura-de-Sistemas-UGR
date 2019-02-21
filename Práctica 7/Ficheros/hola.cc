#include <iostream>
#include <thread>

void hola() { std::cout << "hola"; }

int main()
{
	std::thread t1(hola);
	t1.join();

	std::thread t2([]{ std::cout << " mundo!\n"; });
	t2.join();
}
