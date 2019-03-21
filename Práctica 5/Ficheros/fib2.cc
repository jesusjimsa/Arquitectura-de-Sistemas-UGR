//-----------------------------------------------------------------------------
// fib-0x.cc
//-----------------------------------------------------------------------------

#include <iostream> // cout endl
#include <sstream>  // istringstream ostringstream
#include <future>   // async future

//-----------------------------------------------------------------------------

using namespace std;

//-----------------------------------------------------------------------------

template<class T> T fib(T n)
{
	if (n < 2)
		return n;
	else
		return async(fib<T>, n - 1).get() + async(fib<T>, n - 2).get();
}
//		future<T> n1 = async(fib<T>, n - 1), n2 = async(fib<T>, n - 2);
//		return n1.get() + n2.get();

//-----------------------------------------------------------------------------

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

//-----------------------------------------------------------------------------

