#include <thread>
#include <iostream>

using namespace std;

void hello(int hola){
	cout << hola << endl;
}

int main(){
	thread(hello, i);
}