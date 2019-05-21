//---------------------------------------------------------
// barrera.cc: esqueleto para completar
//---------------------------------------------------------

#include <unistd.h>  // alarm
#include <iostream>  // cout endl
#include <mutex>     // mutex
#include <string>    // string
#include <thread>    // thread
#include <condition_variable>

using namespace std;

//---------------------------------------------------------

const int N = 7;

//---------------------------------------------------------

class barrera_t{
public:
	barrera_t(unsigned _limite): en_espera{0, 0}, limite(_limite), uso(0) {}

	void esperar() {
		unique_lock<mutex> lk(m);
		unsigned uso_local = uso;

		if(++en_espera[uso_local] < limite){
			cv.wait(lk, [&]{return en_espera[uso_local] == 0;});
		}
		else{
			uso = 1 - uso_local;
			en_espera[uso] = 0;
			cv.notify_all();
		}
	}

private:
	mutex m;
	condition_variable cv;
	volatile unsigned en_espera[2];
	unsigned limite, uso;
} barrera(N);

//---------------------------------------------------------

void hebra(int yo){
	string antes = to_string(yo) + ": antes\n";
	string despues = to_string(yo) + ": después\n";

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

