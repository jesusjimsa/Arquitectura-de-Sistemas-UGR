//-----------------------------------------------------------------------------

#include <cassert>
#include <mutex>
#include <iomanip>
#include <iostream>
#include <random>
#include <stack>
#include <unordered_map>
#include <vector>
//#include <boost/multiprecision/cpp_int.hpp>

//-----------------------------------------------------------------------------

template<typename T> T ackermann1(T m, T n)
{
	if (m == 0) return n + 1;
	if (n == 0) return ackermann1(m - 1, T(1));
	return ackermann1(m - 1, ackermann1(m , n - 1));
}

//-----------------------------------------------------------------------------

template<typename T> T ackermann2(T m, T n)
{
	static std::unordered_map<T, std::unordered_map<T, T>> solution;
	
	try
	{
		return solution.at(m).at(n);
	}
	catch(std::out_of_range&)
	{
		if (m == 0) solution[0][n] = n + 1;
		else if (n == 0) solution[m][0] = ackermann2(m - 1, T(1));
		else solution[m][n] = ackermann2(m - 1, ackermann2(m , n - 1));
	}
	
	return solution[m][n];
}

//-----------------------------------------------------------------------------

template<typename T> T ackermann3(T m, T n)
{
	static std::unordered_map<T, std::unordered_map<T, T>> solution;
	
	auto m_found = solution.find(m);
	if (m_found != solution.end())
	{
		auto n_found = m_found->second.find(n);
		if (n_found != m_found->second.end())
			return n_found->second;
	}

	if (m == 0) solution[m][n] = n + 1;
	else if (n == 0) solution[m][n] = ackermann3(m - 1, T(1));
	else solution[m][n] = ackermann3(m - 1, ackermann3(m , n - 1));
	
	return solution[m][n];
}

//-----------------------------------------------------------------------------

template<typename T> T ackermann4(T m, T n)
{
	static const T M = 4, N = 1<<(M*M);
	static T solution[M][N] = {{0}};
	
	assert(m < M && n < N);
	
	if (!solution[m][n])
	{
		if (m == 0)
			solution[0][n] = n + 1;
		else if (n == 0)
			solution[m][0] = ackermann4(m - 1, T(1));
		else
			solution[m][n] = ackermann4(m - 1, ackermann4(m, n - 1));
	}
	
	return solution[m][n];
}

//-----------------------------------------------------------------------------

template<typename T> T ackermann5(T m, T n)
{
	static std::once_flag flag;
	std::call_once(flag, [&]{ ackermann4(T(3), T(11)); });
	
	return ackermann4(m, n);
}

//-----------------------------------------------------------------------------

template<typename T> T ackermann6(T m, T n)
{
	std::stack<T, std::vector<T>> stack({m});
	do {
		m = stack.top();
		stack.pop();
		if (m == 0)
		{
			++n;
		}
		else
		{
			stack.push(m - 1);
			if (n == 0)
			{
				++n;
			}
			else
			{
				stack.push(m);
				--n;
			}
		}
	} while (!stack.empty());
	return n;
}

//-----------------------------------------------------------------------------
/*
using bigint = boost::multiprecision::cpp_int;

bigint ipow(bigint base, bigint exp)
{
	bigint result = 1;
	while (exp)
	{
		if (exp & 1)
			result *= base;
		exp >>= 1;
		base *= base;
	}
	return result;
}

template<typename T> bigint ackermann7(T m, T n)
{
	static bigint (*ack)(unsigned, bigint) = [](unsigned m, bigint n) -> bigint
	{
		switch (m)
		{
			case 0:
				return n + 1;
			case 1:
				return n + 2;
			case 2:
				return 3 + 2 * n;
			case 3:
				return 5 + 8 * (ipow(2, n) - 1);
			default:
				return n == 0 ? ack(m - 1, 1) : ack(m - 1, ack(m, n - 1));
		}
	};
	return ack(m, n);
}

//-----------------------------------------------------------------------------

template<typename T> bigint ackermann8(T m, bigint n) // stack overflow inside!
{
	static std::unordered_map<T, std::unordered_map<T, bigint>> solution
	{
		{ 0, { {0, 1}, {1,  2}, {2,  3}, {3,  4}, {4,   5} } },
		{ 1, { {0, 2}, {1,  3}, {2,  4}, {3,  5}, {4,   6} } }, 
		{ 2, { {0, 3}, {1,  5}, {2,  7}, {3,  9}, {4,  11} } }, 
		{ 3, { {0, 5}, {1, 13}, {2, 29}, {3, 61}, {4, 125} } }
	};
	
	T t = n;
	auto m_found = solution.find(m);
	if (m_found != solution.end())
	{
		auto n_found = m_found->second.find(t);
		if (n_found != m_found->second.end())
			return n_found->second;
	}
	
	if (m == 0) solution[m][t] = n + 1;
	else if (n == 0) solution[m][t] = ackermann8(m - 1, 1);
	else solution[m][t] = ackermann8(m - 1, ackermann8(m , n - 1));
	
	return solution[m][t];
}
*/
//-----------------------------------------------------------------------------

template<typename F> void test(F& f)
{
	const int M = 4, N = 12;
	
	for (int i = 2; i < M; ++i)
		for(int j = 6; j < N; ++j)
			std::cout << f(i, j) << " " << std::flush;
	
	std::mt19937_64 gen(0);
	
	auto start = std::chrono::high_resolution_clock::now();
	
	for (unsigned i = 0; i < 1000; ++i)
	{
		unsigned m = gen() % M, n = gen() % N;
		assert(f(m, n) == ackermann5(m, n));
	}
	
	auto stop = std::chrono::high_resolution_clock::now();
	
	std::chrono::duration<double, std::milli> t(stop - start);
	std::cout << "t = " 
	          << std::fixed << std::setprecision(3) << std::setw(9) << t.count() 
	          << "ms" << std::endl;
}

//-----------------------------------------------------------------------------

int main()
{
	test(ackermann1<unsigned>);
	test(ackermann2<unsigned>);
	test(ackermann3<unsigned>);
	test(ackermann4<unsigned>);
	test(ackermann5<unsigned>);
	test(ackermann6<unsigned>);
//	test(ackermann7<unsigned>);
//	test(ackermann8<unsigned>);
}

//-----------------------------------------------------------------------------
