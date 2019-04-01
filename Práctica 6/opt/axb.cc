#include <algorithm>
#include <chrono>
#include <functional>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <numeric>
#include <random>
#include <typeinfo>

using namespace std;

//-----------------------------------------------------------------------------

const int M = 1234, N = 5678; // multiplos de 2 por quitar if y desenrollar

static_assert(M % 2 == 0 && N % 2 == 0);

//-----------------------------------------------------------------------------

int a[N][M], b[N][M], c[N];

//-----------------------------------------------------------------------------

void reset(){
	static random_device device;
	static default_random_engine generator(device());
	uniform_int_distribution<int> distribution(-5, 5);
	auto rng = bind(distribution, generator);
	
	for (int i = 0; i < N; ++i){
		c[i] = 0;

		for (int j = 0; j < M; ++j){
			a[i][j] = rng();
			b[i][j] = rng();
		}
	}
}

//-----------------------------------------------------------------------------

void f0(){ // original
	for (int i = 0; i < M; ++i){
		for (int j = 0; j < N; ++j){
			if ((j % 2) == 0){
				c[j] += a[j][i] + b[j][i];
			}
			else{
				c[j] += a[j][i] - b[j][i];
			}
		}
	}
}

//-----------------------------------------------------------------------------

void f1(){
	for (int j = 0; j < N - 1; j += 2){
		for (int i = 0; i < M; ++i){
			c[j] += a[j][i] + b[j][i];
			c[j+1] += a[j+1][i] - b[j+1][i];
		}
	}
}

//-----------------------------------------------------------------------------

template<class F> void test(const F& f, const char* name){
	reset();
	
	for (int i = 0; i < 3; ++i){
		f();
	}
	
	const unsigned REP = 25;
	chrono::duration<double, milli> rep[REP];

	for (auto& i: rep){
		auto start = chrono::high_resolution_clock::now();
		f();
		auto stop = chrono::high_resolution_clock::now();

		i = stop - start;
	}
	
	nth_element(begin(rep), begin(rep) + REP / 2, end(rep));
	cout << setw(25) << name << ':'
	          << "  time: " << fixed << setprecision(3) << setw(7)
	          << rep[REP / 2].count() << "ms"
	          << "  result = " <<  accumulate(begin(c), end(c), 0) 
	          << endl;
}

//-----------------------------------------------------------------------------

int main(){
	cout << endl;
	
	test(f0, "original");
	test(f1, "mejorado");
	
	cout << endl;
}

//-----------------------------------------------------------------------------

