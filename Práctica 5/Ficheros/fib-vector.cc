#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>

using namespace std;

template<class T> T fib(T n)
{
	static std::vector<T> solutions = {0, 1};
	static size_t last = 1;
	
	while (n > last)
	{
		++last;
		solutions.push_back(solutions[last - 2] + solutions[last - 1]);
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
