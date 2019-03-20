//---------------------------------------------------------
// ping.pong.thread.cc
//---------------------------------------------------------

#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>

//---------------------------------------------------------

using namespace std::chrono_literals;
using namespace std;

//---------------------------------------------------------

int main(){
	const char PING = '1', PONG = '0';

	atomic<bool> end(false);
	atomic<char> table(PONG);
	int ping = 0, pong = 0;

	thread pingger([&]{
		while(!end){
			while(table == PING);
			table = PING;
			++ping;
		}
	});

	thread pongger([&]{
		while(!end){
			while(table == PONG);
			table = PONG;
			++pong;
		}
	});

	this_thread::sleep_for(1s);
	end = true;

	pingger.join();
	pongger.join();

	cout << "ping = " << ping << endl
	    << "pong = " << pong << endl;
}

//---------------------------------------------------------

