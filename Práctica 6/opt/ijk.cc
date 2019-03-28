#include <cassert>
#include <iomanip>
#include <iostream>
#include <chrono>
#include <random>

const int B = 2, C = 3, N = 1000;

int a[N][N], b[N][N], c[N][N];

void f1(){
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
		{
			a[i][j] = 0;
			for (int k = 0; k < N; ++k)
				a[i][j] += b[i][k] * c[k][j];
		}
}

void f2(){
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			a[i][j] = 0;
	
	for (int i = 0; i < N; ++i)
		for (int k = 0; k < N; ++k)
			for (int j = 0; j < N; ++j)
				a[i][j] += b[i][k] * c[k][j];
}

void f3(){
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			a[i][j] = 0;
	
	for (int j = 0; j < N; ++j)
		for (int i = 0; i < N; ++i)
			for (int k = 0; k < N; ++k)
				a[i][j] += b[i][k] * c[k][j];
}

void f4(){
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			a[i][j] = 0;
	
	for (int j = 0; j < N; ++j)
		for (int k = 0; k < N; ++k)
			for (int i = 0; i < N; ++i)
				a[i][j] += b[i][k] * c[k][j];
}

void f5(){
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			a[i][j] = 0;
	
	for (int k = 0; k < N; ++k)
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < N; ++j)
				a[i][j] += b[i][k] * c[k][j];
}

void f6(){
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			a[i][j] = 0;
	
	for (int k = 0; k < N; ++k)
		for (int j = 0; j < N; ++j)
			for (int i = 0; i < N; ++i)
				a[i][j] += b[i][k] * c[k][j];
}

template<class F> void test(F& f){
	f();
	auto start = std::chrono::high_resolution_clock::now();
	f();
	auto stop = std::chrono::high_resolution_clock::now();
	
	std::chrono::duration<double, std::milli> t = (stop - start);
	std::cout << "time = " << std::fixed << std::setprecision(2) << std::setw(8) 
	          << t.count() << "ms" << std::endl;
	
	assert(a[999][999] == B * C * N);
}

int main(){
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j){
			b[i][j] = B;
			c[i][j] = C;
		}
	
	test(f1);
	test(f2);
	test(f3);
	test(f4);
	test(f5);
	test(f6);
}

