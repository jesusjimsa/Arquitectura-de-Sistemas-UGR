#include <future>
#include <iostream>
#include <sstream>
#include <thread>

void codigo()
{
	std::stringstream oss;
	oss << "[" << std::this_thread::get_id() << "]: hola!\n";
	std::cout << oss.str();
}

int main()
{
	codigo();
	std::thread t(codigo);
	auto a = std::async(codigo);
	t.join();
}
