#include <iostream>
#include <cmath>

using namespace std;

template<typename T> T ackermann(T m, T n){
	unsigned int sol = 0;

	/*
		https://en.wikipedia.org/wiki/Ackermann_function#Table_of_values
	*/
	switch (m){
		case 0:
			sol = n + 1;
			
			break;
		case 1:
			sol = n + 2;

			break;
		case 2:
			sol = 2 * n + 3;

			break;
		case 3:
			sol = 8 * pow(2, n) - 3;

			break;
	}

	return sol;
}

int main(){
	for (int m = 0; m < 4; ++m){
		for (int n = 0; n < 13; ++n){
			cout << "ackermann(" << m << ", " << n << ") = " << ackermann(m, n) << endl;
		}
	}
}