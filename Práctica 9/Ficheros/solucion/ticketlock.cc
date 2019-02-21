//----------------------------------------------------
// ticketlock.cc
//----------------------------------------------------

#include <unistd.h>
#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>

//----------------------------------------------------

using namespace std;

//----------------------------------------------------

const int N = 16;

//----------------------------------------------------

class ticketlock
{
public:
	ticketlock(): next{0}, now{0} {}

	void adquirir()
	{
		unsigned my_ticket = next++;
		while(my_ticket != now)
			this_thread::sleep_for(chrono::microseconds((my_ticket - now) << 4));
	}

	void liberar()
	{
		++now;
	}

private:
	atomic<unsigned> next, now; // tickets
} c;

//----------------------------------------------------

void seccion_critica()
{
	cout << "[" << this_thread::get_id() << "]: ";
	for(int i = 0; i < 10; ++i)
		cout << i;
	cout << endl;
}

//----------------------------------------------------

void hebra()
{
	while(true)
	{
		c.adquirir();
		seccion_critica();
		c.liberar();
	}
}

//----------------------------------------------------

int main()
{
	thread t[N];
	
	alarm(1);
	for(auto& i: t) i = thread(hebra);
	for(auto& i: t) i.join();
}

//----------------------------------------------------
