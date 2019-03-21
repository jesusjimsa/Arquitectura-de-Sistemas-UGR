#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <thread>

using namespace std;

template<class T> T fib(T n, T &res){
	if (n < 2){
		res = n;

		return res;
	}
	else{
		T res1, res2;

		thread(fib, n - 1, res1);
		thread(fib, n - 2, res2);

		return res1 + res2;
	}
}

int main(int argc, char *argv[]){
	if (argc < 2){
		throw invalid_argument("Necesito un número como parámetro");
	}

	unsigned long long resultado = 0.0;

	istringstream iss(argv[1]);
	
	unsigned long long n;
	iss >> n;
	
	if (!iss){
		throw invalid_argument("El parámetro no es un número válido");
	}

	cout << argv[0] << "(" << argv[1] << ") = " << fib(n, resultado) << endl;
}
