// unlimited number of threads

#include <thread>
#include "work.h"

using namespace std;

int main(){
	thread t[N];

	for (int i = 0; i < N; ++i){
		t[i] = thread(work, i, i + 1);
	}

	for (auto& i: t){
		i.join();
	}
}
