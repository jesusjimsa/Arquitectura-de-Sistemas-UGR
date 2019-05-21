//---------------------------------------------------------
// barrera-ceo.cc: barrera con espera ocupada
//---------------------------------------------------------

#include <unistd.h>  // alarm
#include <iostream>  // cout endl
#include <mutex>     // mutex
#include <string>    // string
#include <thread>    // thread
#include <semaphore.h>

using namespace std;

//---------------------------------------------------------

const int N = 7;

//---------------------------------------------------------

class barrera_t{
public:
	barrera_t(unsigned _limite): uso(0), limite(_limite) {
		sem_init(&sem[0], 0, 0);
		sem_init(&sem[1], 0, 0);
	}

	void esperar(){
		unsigned uso_local = uso;
		unsigned value;

		m.lock();
		sem_post(&sem[uso_local]);
		m.unlock();

		sem_wait(sem[uso_local]);
	}

private:
	mutex m;
	sem_t sem[2];
	volatile unsigned uso;
	unsigned limite;
} barrera(N);

//---------------------------------------------------------

void hebra(int yo){
	string   antes = to_string(yo) +   ": antes\n",
	            despues = to_string(yo) + ": después\n";

	while(true){
		cout << antes;
		barrera.esperar();
		cout << despues;
	}
}

//---------------------------------------------------------

int main(){
	alarm(1);
	thread t[N];

	for (int i = 0; i < N; ++i){
		t[i] = thread(hebra, i);
	}

	for (auto& i: t){
		i.join();
	}
}

//---------------------------------------------------------

