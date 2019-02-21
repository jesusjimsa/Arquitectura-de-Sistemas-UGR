// optimal number of threads

#include <thread>
#include "work.h"

int main()
{
	const int T = std::thread::hardware_concurrency();
	
	std::thread t[T];
	
	for (int i = 0; i < T; ++i)
		t[i] = std::thread(work, i * (N / T), (i + 1) * (N / T));
	
	for (auto& i: t)
		i.join();
}
