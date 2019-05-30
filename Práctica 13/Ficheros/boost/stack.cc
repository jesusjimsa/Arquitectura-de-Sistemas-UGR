#include <atomic>
#include <chrono>
#include <iostream>
#include <random>
#include <thread>
#include <boost/lockfree/stack.hpp>

using namespace std::chrono_literals;

std::atomic<bool> run(true);
std::atomic<std::size_t> push(0), pop(0);
boost::lockfree::stack<int> s(1000);

void work()
{
	std::default_random_engine engine;
	
	while (run)
	{
		if (engine() & 1)
		{
			s.push(engine());
			++push;
		}
		else
		{
			int i;
			s.pop(i);
			++pop;
		}
	}
}

int main()
{
	const std::size_t N = std::thread::hardware_concurrency();
	
	std::thread workers[N];
	
	for (auto& w: workers)
		w = std::thread(work);
	
	std::this_thread::sleep_for(333ms);
	run = false;

	for (auto& w: workers)
		w.join();

	std::cout << push << ' ' << pop << std::endl;
}
