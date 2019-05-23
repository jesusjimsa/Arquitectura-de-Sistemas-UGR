//-----------------------------------------------------
// le.cc: condición de carrera + inanición
//-----------------------------------------------------

#include <atomic>
#include <chrono>
#include <iostream>
#include <random>
#include <thread>
#include <mutex>
#include <semaphore.h>

//-----------------------------------------------------

using namespace std;

//-----------------------------------------------------

const unsigned N = 8;
atomic<bool> run(true);
mutex mtx;
sem_t sem;

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
		sem_wait(&sem);
		seccion_critica('0');
		sem_post(&sem);
	}
}

//-----------------------------------------------------

void escritor(){
	while (run){
		mtx.lock();

		for (unsigned i = 0; i < N; ++i){
			sem_wait(&sem);
		}

		mtx.unlock();

		seccion_critica('a');

		for (unsigned i = 0; i < N; ++i){
			sem_post(&sem);
		}
	}
}

//-----------------------------------------------------

int main(){
	thread lectores[N], escritores[N];
	default_random_engine engine;

	sem_init(&sem, 0, N);

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
