// http://preshing.com/20120515/memory-reordering-caught-in-the-act

#include <atomic>
#include <functional>
#include <iostream>
#include <mutex>
#include <random>
#include <thread>

int x, y, r1, r2;
unsigned reorders = 0, iterations = 0;
std::atomic<bool> run(true);
std::mutex m1, m2, m3, m4;
std::ranlux24_base e;
std::uniform_int_distribution<unsigned> d(0, 7);
auto rng = std::bind(d, e);

void t1()
{
	while(run)
	{
		m1.lock();
		while (rng() != 0);
		x = 1;
		asm volatile ("mfence":::"memory");
		r1 = y;
		m3.unlock();
	}
}

void t2()
{
	while(run)
	{
		m2.lock();
		while (rng() != 0);
		y = 1;
		asm volatile ("mfence":::"memory");
		r2 = x;
		m4.unlock();
	}
}

void t3()
{
	while (run)
	{
		x = 0;
		y = 0;
		m1.unlock();
		m2.unlock();
		m3.lock();
		m4.lock();
		if (r1 == 0 && r2 == 0) 
			++reorders;
		++iterations;
	}
}

int main()
{
	std::lock(m1, m2, m3, m4);
	std::thread t[] = {std::thread(t1), std::thread(t2), std::thread(t3)};
	
	std::this_thread::sleep_for(std::chrono::milliseconds(250));
	run = false;
	m1.unlock();
	m2.unlock();
	for (auto& i: t) i.join();
	
	std::cout << reorders << " reorders detected after " 
	          << iterations << " iterations" << std::endl;
}
