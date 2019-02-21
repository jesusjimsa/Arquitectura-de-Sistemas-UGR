//---------------------------------------------------------
// ping.pong.thread.cc
//---------------------------------------------------------

#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>

//---------------------------------------------------------

using namespace std::chrono_literals;

//---------------------------------------------------------

int main()
{
	const char PING = '1', PONG = '0';

	std::atomic<bool> end(false);
	std::atomic<char> table(PONG);
	int ping = 0, pong = 0;

	std::thread pingger([&]
	{
		while(!end)
		{
			while(table == PING);
			table = PING;
			++ping;
		}
	});

	std::thread pongger([&]
	{
		while(!end)
		{
			while(table == PONG);
			table = PONG;
			++pong;
		}
	});

	std::this_thread::sleep_for(1s);
	end = true;

	pingger.join();
	pongger.join();

	std::cout << "ping = " << ping << std::endl
	          << "pong = " << pong << std::endl;
}

//---------------------------------------------------------

