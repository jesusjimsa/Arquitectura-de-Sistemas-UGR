#include <atomic>
#include <chrono>
#include <functional>
#include <iostream>
#include <random>
#include <thread>
#include "stack.h"

using namespace std::chrono_literals;

std::atomic<bool> run(true);
std::atomic<std::size_t> push(0), pop(0);
stack<int> s;

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
			try { s.pop(); } catch(typename stack<int>::empty&) {}
			++pop;
		}
	}
}

int main()
{
	const std::size_t N = 1;
	
	std::thread workers[N];
	
	for (auto& w: workers)
		w = std::thread(work);
	
	std::this_thread::sleep_for(333ms);
	run = false;

	for (auto& w: workers)
		w.join();

	std::cout << push << ' ' << pop << std::endl;
}
