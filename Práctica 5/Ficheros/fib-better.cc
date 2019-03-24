#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <future>   // async future

using namespace std;

template<class T> T fib(T n){
	if (n < 2){
		return n;
	}
	else{
		return async(fib<T>, n - 1).get() + async(fib<T>, n - 2).get();
	}
}

int main(int argc, char *argv[]){
	if (argc < 2){
		throw invalid_argument("Necesito un número como parámetro");
	}

	istringstream iss(argv[1]);
	
	unsigned long long n;
	iss >> n;
	
	if (!iss){
		throw invalid_argument("El parámetro no es un número válido");
	}

	cout << argv[0] << "(" << argv[1] << ") = " << fib(n) << endl;
}
