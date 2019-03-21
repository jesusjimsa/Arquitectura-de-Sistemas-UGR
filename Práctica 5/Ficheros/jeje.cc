#include <thread>
#include <iostream>

using namespace std;

void hello(int hola){
	cout << hola << endl;
}

int main(){
	for(int i = 0; i < 2; i++){
		thread(hello, i);
	}
}