#include <iostream>
#include <thread>

int main()
{
	std::cout << "[1] hola: " 
	          << std::this_thread::get_id() 
	          << std::endl;
	
	std::thread t([]
	{
		std::cout << "[2] hola: " 
		          << std::this_thread::get_id() 
		          << std::endl;
	});
	t.join();
}
