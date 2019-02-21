#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace std;

template<class T> T fib(T n)
{
	static const size_t N = 1000;
	static size_t last = 1;
	static T solutions[N] = {0, 1};
	
	if (n > last)
	{
		solutions[n] = fib(n - 2) + fib(n - 1);
		last = n;
	}
	
	return solutions[n];
}

int main(int argc, char *argv[])
{
	if (argc < 2)
		throw invalid_argument("necesito un número como parámetro");

	istringstream iss(argv[1]);
	unsigned long long n;
	iss >> n;
	if (!iss)
		throw invalid_argument("el parámetro no es un número válido");

	cout << argv[0] << "(" << argv[1] << ") = " << fib(n) << endl;
}
