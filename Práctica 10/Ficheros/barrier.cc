//---------------------------------------------------------
// barrera.cc: esqueleto para completar
//---------------------------------------------------------

#include <unistd.h>  // alarm
#include <iostream>  // cout endl
#include <mutex>     // mutex
#include <string>    // string
#include <thread>    // thread
#include <pthread.h>

using namespace std;

//---------------------------------------------------------

const int N = 7;
pthread_barrier_t barrier;

//---------------------------------------------------------

void hebra(int yo){
	string antes = to_string(yo) + ": antes\n";
	string despues = to_string(yo) + ": después\n";
	
	while(true){
		cout << antes;
		pthread_barrier_wait(&barrier);
		cout << despues;
	}
}

//---------------------------------------------------------

int main(){
	alarm(1);
	thread t[N];

	pthread_barrier_init(&barrier, 0, N);

	for (int i = 0; i < N; ++i){
		t[i] = thread(hebra, i);
	}

	for (auto& i: t){
		i.join();
	}
}

//---------------------------------------------------------

