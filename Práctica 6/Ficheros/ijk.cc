#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>

const int N = 512;

int s[N][N], v1[N][N], v2[N][N];

void f1()
{
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			for (int k = 0; k < N; ++k)
				s[i][j] += v1[i][k] * v2[k][j];
}

void f2()
{
	for (int i = 0; i < N; ++i)
		for (int k = 0; k < N; ++k)
				for (int j = 0; j < N; ++j)
						s[i][j] += v1[i][k] * v2[k][j];
}

void f3()
{
	for (int k = 0; k < N; ++k)
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < N; ++j)
				s[i][j] += v1[i][k] * v2[k][j];
}

void f4()
{
	for (int k = 0; k < N; ++k)
		for (int j = 0; j < N; ++j)
			for (int i = 0; i < N; ++i)
				s[i][j] += v1[i][k] * v2[k][j];
}

void f5()
{
	for (int j = 0; j < N; ++j)
		for (int k = 0; k < N; ++k)
			for (int i = 0; i < N; ++i)
				s[i][j] += v1[i][k] * v2[k][j];
}

void f6()
{
	for (int j = 0; j < N; ++j)
		for (int i = 0; i < N; ++i)
			for (int k = 0; k < N; ++k)
				s[i][j] += v1[i][k] * v2[k][j];
}

__attribute__((optimize("-fno-inline")))
void test(void (*f)(void))
{
	for (int i = 0; i < 5; ++i)
		f();
}

int main()
{
	// inicializar
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
		{
			 s[i][j] = 1;
			v1[i][j] = 2;
			v2[i][j] = 3;
		}
	
	test(f1);
	test(f2);
	test(f3);
	test(f4);
	test(f5);
	test(f6);
}
