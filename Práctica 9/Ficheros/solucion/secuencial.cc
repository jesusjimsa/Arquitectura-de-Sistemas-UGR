//----------------------------------------------------
// secuencial.cc
//----------------------------------------------------

#include <unistd.h>
#include <iostream>
#include <thread>

//----------------------------------------------------

using namespace std;

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
		seccion_critica();
	}
}

//----------------------------------------------------

int main()
{
	alarm(1);
	hebra();
}

//----------------------------------------------------
