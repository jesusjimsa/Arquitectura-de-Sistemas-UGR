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

void msg(int yo, const char *txt)
{
	static std::mutex m;
	std::unique_lock<std::mutex> l(m);
	std::cout << yo << ": " << txt << std::endl;
}

//---------------------------------------------------------

void hebra(int yo)
{
	while(true)
	{
		msg(yo, "antes");
		barrera.esperar();
		msg(yo, "después");
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

