//----------------------------------------------------
// mutex.cc
//----------------------------------------------------

#include <unistd.h>
#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>
#include <mutex>

//----------------------------------------------------

using namespace std;

//----------------------------------------------------

const int N = 16;
mutex mtx;

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
		mtx.lock();
		seccion_critica();
		mtx.unlock();
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
