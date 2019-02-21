#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>
#include "stack.h"

std::atomic<bool> run(true);
std::atomic<unsigned> push(0), pop(0);
stack<int> s;

void pusher()
{
	while (run)
	{
		s.push(new stack<int>::node);
		++push;
	}
}

void popper()
{
	while (run)
	{
		delete s.pop();
		++pop;
	}
}

int main()
{
	const unsigned N = std::max(2u, std::thread::hardware_concurrency());

	std::thread pushers[N / 2], poppers[N / 2];

	for (auto& i: pushers) i = std::thread(pusher);
	for (auto& i: poppers) i = std::thread(popper);

	std::this_thread::sleep_for(std::chrono::milliseconds(333));
	run = false;

	for (auto& i: pushers) i.join();
	for (auto& i: poppers) i.join();

	std::cout << push << ' ' << pop << std::endl;
}
