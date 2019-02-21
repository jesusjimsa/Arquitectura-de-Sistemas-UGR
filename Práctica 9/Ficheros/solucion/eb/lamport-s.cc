//----------------------------------------------------
// lamport-s.cc
//----------------------------------------------------

#include <unistd.h>
#include <algorithm>
#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>

//----------------------------------------------------

using namespace std;

//----------------------------------------------------

const int N = 16;

volatile bool escoger[N]{false};
volatile int numero[N]{0};

//----------------------------------------------------

void seccion_critica()
{
	cout << "[" << this_thread::get_id() << "]: ";
	for(int i = 0; i < 10; ++i)
		cout << i;
	cout << endl;
}

//----------------------------------------------------

void hebra(int i)
{
	while(true)
	{
		escoger[i] = true;
		numero[i] = *max_element(&numero[0], &numero[0] + N) + 1;
		escoger[i] = false;
		for (int j = 0; j < N; ++j)
		{
			auto delay = 125us;
			while (escoger[j]);
			while (numero[j] != 0 && (numero[j]  < numero[i] ||
		                             (numero[j] == numero[i] && j < i)))
				this_thread::sleep_for(delay *= 2);
		}
		seccion_critica();
		numero[i] = 0;
	}
}

//----------------------------------------------------

int main()
{
	thread t[N];
	
	alarm(1);
	for(int i = 0; i < N; ++i) t[i] = thread(hebra, i);
	for(auto& i: t) i.join();
}

//----------------------------------------------------
