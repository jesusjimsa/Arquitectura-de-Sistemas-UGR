//-----------------------------------------------------
// le.cc: condición de carrera + inanición
//-----------------------------------------------------

#include <atomic>
#include <chrono>
#include <iostream>
#include <random>
#include <thread>
#include <mutex>
#include <interruptor.h>

//-----------------------------------------------------

using namespace std;

//-----------------------------------------------------

atomic<bool> run(true);
interruptor interr;
mutex torno, nadie;

//-----------------------------------------------------

void seccion_critica(char c){
	for (char i = 0; i < 10; ++i){
		cout << c++;
	}

	cout << endl;
}

//-----------------------------------------------------

void lector(){
	while (run){
		torno.lock();
		torno.unlock();
		interr.lock(nadie);
		seccion_critica('0');
		interr.unlock(nadie);
	}
}

//-----------------------------------------------------

void escritor(){
	while (run){
		torno.lock();
		nadie.lock();
		seccion_critica('a');
		torno.unlock();
		nadie.unlock();
	}
}

//-----------------------------------------------------

int main(){
	const unsigned N = 8;
	thread lectores[N], escritores[N];
	default_random_engine engine;

	for (unsigned i = 0; i < N; ++i){
		if (engine() & 1){
			lectores[i] = thread(lector);
			escritores[i] = thread(escritor);
		}
		else{
			escritores[i] = thread(escritor);
			lectores[i] = thread(lector);
		}
	}

	this_thread::sleep_for(1s);
	run = false;

	for(thread& i: lectores){
		i.join();
	}

	for(thread& i: escritores){
		i.join();
	}
}

//-----------------------------------------------------
