#include <iostream>

using namespace std;

template<typename T> T ackermann(T m, T n){
	if (m == 0){
		return n + 1;
	}

	if (n == 0){
		return ackermann(m - 1, 1);
	}
	
	return ackermann(m - 1, ackermann(m , n - 1));
}

int main(){
	for (int m = 0; m < 4; ++m){
		for (int n = 0; n < 13; ++n){
			cout << "ackermann(" << m << ", " << n << ") = " << ackermann(m, n) << endl;
		}
	}
}
