#include <cassert>

const int N = 1000;

int v1[N][N], v2[N][N], v3[N][N];

void work(int begin, int end)
{
	for (int i = begin; i < end; ++i)
		for (int k = 0; k < N; ++k)
			for (int j = 0; j < N; ++j)
				v3[i][j] += v1[i][k] * v2[k][j];
}

