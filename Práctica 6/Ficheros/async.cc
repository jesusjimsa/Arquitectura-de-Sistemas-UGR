#include <chrono>
#include <functional>
#include <future>
#include <iostream>
#include <random>
#include <string>
#include <thread>
#include <vector>

int main()
{
	std::vector<std::future<void>> v;

	std::random_device rd;
	std::default_random_engine generator(rd());
	std::uniform_int_distribution<int> distribution(1000, 2000);
	auto rng = std::bind(distribution, generator);

	for (int i = 0; i < 5; ++i)
		v.push_back(std::async(std::launch::async, [&](int x)
		{
			while(true)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(rng()));
				std::cout << x << std::flush;
			}
		}, i));

	for (auto& i: v)
		i.wait();
}
