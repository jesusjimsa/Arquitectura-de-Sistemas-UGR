#include <atomic>
#include <chrono>
#include <iostream>
#include <random>
#include <thread>
#include "stack.h"

std::atomic<bool> run(true);
unsigned push = 0, pop = 0;

void work()
{
	std::default_random_engine engine;
	stack<int> s;
	
	while (run)
	{
		if (engine() & 1)
		{
			s.push(new stack<int>::node);
			++push;
		}
		else
		{
			delete s.pop();
			++pop;
		}
	}
}

int main()
{
	std::thread worker(work);

	std::this_thread::sleep_for(std::chrono::milliseconds(333));
	run = false;

	worker.join();

	std::cout << push << ' ' << pop << std::endl;
}
