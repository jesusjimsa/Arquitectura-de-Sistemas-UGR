//---------------------------------------------------------
// urrea.cc
//---------------------------------------------------------

#include <unistd.h>     // alarm
#include <atomic>       // atomic
#include <chrono>       // us
#include <iostream>     // cout endl
#include <shared_mutex> // shared_mutex
#include <thread>       // thread

using namespace std::chrono;

//---------------------------------------------------------

const int N = 32;

//---------------------------------------------------------

std::condition_variable_any cond_var;

class ThreadSafeBarrier {
   public:
 
   void esperar() {
      std::unique_lock<std::shared_mutex> lock(mutex_);
      value++;
      if (value < N){
         cond_var.wait(lock);
      }else{
         cond_var.notify_all();
         value=0;
      }
   }


   private:
      mutable std::shared_mutex mutex_;
      unsigned int value = 0;
} barrera;

//---------------------------------------------------------

void hebra(int yo)
{
	std::string   antes = std::to_string(yo) +   ": antes\n", 
	            despues = std::to_string(yo) + ": después\n";
	while(true)
	{
		std::cout << antes;
		barrera.esperar();
		std::cout << despues;
	}
}
//---------------------------------------------------------

int main()
{
	alarm(1);
	std::thread t[N];
	for (int i = 0; i < N; ++i) t[i] = std::thread(hebra, i);
	for (auto& i: t) i.join();
}

//---------------------------------------------------------

