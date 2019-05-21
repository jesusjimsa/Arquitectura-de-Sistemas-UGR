//---------------------------------------------------------
// barrera-ceo.cc: barrera con espera ocupada
//---------------------------------------------------------

#include <unistd.h>  // alarm
#include <iostream>  // cout endl
#include <mutex>     // mutex
#include <string>    // string
#include <thread>    // thread

using namespace std;

//---------------------------------------------------------

const int N = 7;

//---------------------------------------------------------

class barrera_t{
public:
	barrera_t(unsigned _limite): en_espera{0, 0}, uso(0), limite(_limite) {}

	void esperar(){
		unsigned uso_local = uso;

		m.lock();
		++en_espera[uso_local];
		m.unlock();

		if (en_espera[uso_local] == limite){
			uso = 1 - uso;
			en_espera[uso_local] = 0;
		}
		else{
			while(en_espera[uso_local] > 0);
		}
	}

private:
	mutex m;
	volatile unsigned en_espera[2], uso;
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

