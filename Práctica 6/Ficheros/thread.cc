#include <atomic>
#include <chrono>
#include <functional>
#include <iostream>
#include <mutex>
#include <thread>
#include <utility>

std::mutex m;

void f1(int n)
{
	for (int i = 0; i < 5; ++i)
	{
		{
			std::lock_guard<std::mutex> lg(m);
			std::cout << "f1 is executing in thread " 
			          << std::this_thread::get_id() << std::endl;
		}
		++n;
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}
 
void f2(int& n)
{
	for (int i = 0; i < 5; ++i)
	{
		{
			std::lock_guard<std::mutex> lg(m);
			std::cout << "f2 is executing in thread " 
			          << std::this_thread::get_id() << std::endl;
		}
		++n;
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}
 
int main()
{
	int n = 0;
	std::thread t1; // t1 is not a thread
	std::thread t2(f1, n + 1); // pass by value
	std::thread t3(f2, std::ref(n)); // pass by reference
	std::thread t4(std::move(t3)); // t4 is now running f2(). t3 is no longer a thread
	t2.join();
	t4.join();
	std::cout << "Final value of n is " << n << '\n';
}
