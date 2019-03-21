#include <iostream>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <vector>

using namespace std;

template<class T> T fib(T n)
{
	static std::vector<T> solutions = {0, 1};
	
	std::size_t last = solutions.size();
	
	if (last <= n)
	{
		solutions.resize(n + 1);
		for (auto i = solutions.begin() + last; i != solutions.end(); ++i)
			*i = *(i - 2) + *(i - 1);
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
