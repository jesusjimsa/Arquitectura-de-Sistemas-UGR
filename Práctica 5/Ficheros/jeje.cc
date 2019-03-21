#include <thread>
#include <iostream>

using namespace std;

void hello(int hola){
	cout << hola << endl;
}

int main(){
	int i = 10;

	thread(hello, std::cref(i));
}