// unlimited number of threads

#include <thread>
#include "work.h"

int main()
{
	std::thread t[N];
	
	for (int i = 0; i < N; ++i)
		t[i] = std::thread(work, i, i + 1);
	
	for (auto& i: t)
		i.join();
}
