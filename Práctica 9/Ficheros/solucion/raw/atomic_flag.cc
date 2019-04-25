//----------------------------------------------------
// atomic_flag.cc
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

class cerrojo
{
public:
	cerrojo(): cerrado(ATOMIC_FLAG_INIT) {}
	void adquirir() { while (cerrado.test_and_set(memory_order_acquire)); }
	void liberar() { cerrado.clear(memory_order_release); }

private:
	atomic_flag cerrado;
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
	alarm(1);
	thread t[N];
	
	alarm(1);
	for(auto& i: t) i = thread(hebra);
	for(auto& i: t) i.join();
}

//----------------------------------------------------
