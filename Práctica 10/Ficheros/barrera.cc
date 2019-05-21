//---------------------------------------------------------
// barrera.cc: esqueleto para completar
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
	barrera_t(unsigned _limite) {}
	void esperar() {}
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

