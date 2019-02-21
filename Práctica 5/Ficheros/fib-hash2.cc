#include <iostream>
#include <sstream>
#include <stdexcept>
#include <unordered_map>

using namespace std;

template<class T> T fib(T n)
{
	static std::unordered_map<T, T> solutions = {{0, 0}, {1, 1}};

	if (solutions.find(n) == solutions.end())
		solutions[n] = fib(n - 2) + fib(n - 1);

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
