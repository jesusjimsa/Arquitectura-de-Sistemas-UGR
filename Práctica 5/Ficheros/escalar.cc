#include <algorithm>
#include <cassert>
#include <iostream>

const int N = 1000;

int s[N][N], v1[N][N], v2[N][N];

int main()
{
	// inicializar
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
		{
				 s[i][j] = 0;
				v1[i][j] = 1;
				v2[i][j] = 2;
		}
	
	// multiplicar s = v1 x v2
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			for (int k = 0; k < N; ++k)
				s[i][j] += v1[i][k] * v2[k][j];
	
	// verificar
	// assert(std::find_if(std::begin(s), std::end(s), std::not1(v1[0][0] * v2[0][0] * N)) == std::end(s));
}
