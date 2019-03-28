const int N = 1 << 25;

int f1()
{
	int r = 0;
	for (int i = 0; i < N; ++i)
		r += i;
	return r;
}

int f2()
{
	int r = 0;
	for (int i = 0; i < 2 * N; ++i)
		r += i;
	return r;
}

int main()
{
	return f1() + f2();
}
