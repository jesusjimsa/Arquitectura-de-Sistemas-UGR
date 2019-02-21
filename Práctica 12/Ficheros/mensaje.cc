const int N = 250;

int listo = 0;
int mensaje[N];

void f(int i)
{
	mensaje[i % N] = 42;
	listo = 1;
}

int main()
{
	for (int i = 0; i < N; ++i)
		f(i);
}
