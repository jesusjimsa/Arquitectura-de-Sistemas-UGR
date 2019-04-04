// optimal number of threads

#include <thread>
#include "work.h"

using namespace std;

int main(){
	const int T = thread::hardware_concurrency();

	thread t[T];

	for(int i = 0; i < T; ++i){
		t[i] = thread(work, i * (N / T), (i + 1) * (N / T));
	}

	for(auto& i: t){
		i.join();
	}
}
