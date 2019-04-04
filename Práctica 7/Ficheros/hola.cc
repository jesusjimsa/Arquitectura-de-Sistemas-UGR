#include <iostream>
#include <thread>

using namespace std;

void hola(){
	cout << "hola";
}

int main(){
	thread t1(hola);
	t1.join();

	thread t2([]{ cout << " mundo!\n"; });
	t2.join();
}
