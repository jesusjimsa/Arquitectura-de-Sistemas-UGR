//-----------------------------------------------------
// le.cc: condición de carrera + inanición
//-----------------------------------------------------

#include <atomic>
#include <chrono>
#include <iostream>
#include <random>
#include <thread>
#include <mutex>

//-----------------------------------------------------

using namespace std;

//-----------------------------------------------------

atomic<bool> run(true);
mutex no_lectores, no_escritores;
int num_lectores = 0;

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
		no_lectores.lock();
		
		++num_lectores;
		
		if(num_lectores == 1){
			no_escritores.lock();
		}

		no_lectores.unlock();

		seccion_critica('0');

		no_lectores.lock();

		--num_lectores;
		
		if(num_lectores == 0){
			no_escritores.unlock();
		}

		no_lectores.unlock();
	}
}

//-----------------------------------------------------

void escritor(){
	while (run){
		no_escritores.lock();
		seccion_critica('a');
		no_escritores.unlock();
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
