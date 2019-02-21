#include <pthread.h>
#include <iomanip>
#include <iostream>
#include <thread>

int main()
{
	std::cout << std::setw(30) 
	          << "pthread_self() = " 
	          << pthread_self() 
	          << std::endl
	          << std::setw(30) 
	          << "std::this_thread::get_id() = " 
	          << std::this_thread::get_id() 
	          << std::endl;
}
