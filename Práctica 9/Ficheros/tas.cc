//----------------------------------------------------
// tas.cc
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

bool test_and_set(volatile bool *spinlock){
	bool ret;
	
	__asm__ __volatile__(
		"lock xchgb %0, %1"
		: "=r" (ret), "=m" (*spinlock)
		: "0" (true), "m" (*spinlock)
		: "memory"
	); 
	
	return ret;
}

//----------------------------------------------------

class cerrojo {
public:
	cerrojo(): cerrado(false) {} // inicialmente abierto

	void adquirir() {
		while (test_and_set(&cerrado));
	}

	void liberar() {
		cerrado = false; // abrir
	}
private:
	bool cerrado;
} c;

//----------------------------------------------------

void seccion_critica(){
	cout << "[" << this_thread::get_id() << "]: ";
	for(int i = 0; i < 10; ++i)
		cout << i;
	cout << endl;
}

//----------------------------------------------------

void hebra(){
	while(true){
		c.adquirir();
		seccion_critica();
		c.liberar();
	}
}

//----------------------------------------------------

int main(){
	thread t[N];
	
	alarm(1);
	for(auto& i: t) i = thread(hebra);
	for(auto& i: t) i.join();

}

//----------------------------------------------------
