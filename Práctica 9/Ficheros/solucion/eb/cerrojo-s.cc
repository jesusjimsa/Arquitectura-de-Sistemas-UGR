//----------------------------------------------------
// cerrojo-s.cc
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
	cerrojo(): cerrado(false) {}

	void adquirir()
	{
		auto delay = 125us;
		while (cerrado)
			this_thread::sleep_for(delay *= 2);
		cerrado = true;
	}

	void liberar()
	{
		cerrado = false;
	}
	
private:
	volatile bool cerrado;
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
