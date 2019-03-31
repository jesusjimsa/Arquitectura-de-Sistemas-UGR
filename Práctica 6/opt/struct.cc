//-----------------------------------------------------------------------------
// struct.cc
//-----------------------------------------------------------------------------

#include <chrono>
#include <functional>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <random>
#include <typeinfo>

using namespace std;

//-----------------------------------------------------------------------------

const int N = 10000, REP = 10000;

//-----------------------------------------------------------------------------

random_device device;
default_random_engine generator(device());
uniform_int_distribution<int> distribution(0, 9);
auto rng = bind(distribution, generator);

//-----------------------------------------------------------------------------

struct S {
	int a, b;
	S(): a(rng()), b(rng()) {}
} const s[N];

int R[REP + 1]; // because... for (int ii = 1; ii <= REP; ++ii)

//-----------------------------------------------------------------------------

void v0(){
	for (int ii = 1; ii <= REP; ++ii){
		int X1 = 0, X2 = 0;

		for(int i = 0; i < N; ++i){
			X1 += 2 * s[i].a + ii;
		}

		for(int i = 0; i < N; ++i){
			X2 += 3 * s[i].b - ii;
		}

		if (X1 <  X2){
			R[ii] = X1;
		}
		else{
			R[ii] = X2;
		}
	}
}

//-----------------------------------------------------------------------------

void v1(){
	for (int ii = 1; ii <= REP; ++ii){
		int X1 = 0, X2 = 0;

		for(int i = 0; i < N; ++i){
			X1 += 2 * s[i].a + ii;
			X2 += 3 * s[i].b - ii;
		}

		if (X1 <  X2){
			R[ii] = X1;
		}
		else{
			R[ii] = X2;
		}
	}
}

//-----------------------------------------------------------------------------

template<class F> void test(F& f, const char* name){
	fill(R, R + REP, 0);

	for (int i = 0; i < 3; ++i){
		f();
	}

	auto start = chrono::high_resolution_clock::now();
	f();
	auto stop = chrono::high_resolution_clock::now();

	cout << "function: " << name << "\t time: " << setw(7)
			  << chrono::duration_cast<chrono::microseconds>(stop - start).count()
			  << "us\t result = " <<  accumulate(R + 1, R + REP + 1, 0) << endl;
}

//-----------------------------------------------------------------------------

int main(){
	test(v0, "v0");
	test(v1, "v1");
}

//-----------------------------------------------------------------------------

