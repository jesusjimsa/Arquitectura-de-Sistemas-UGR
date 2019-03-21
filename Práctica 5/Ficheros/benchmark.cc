//-----------------------------------------------------------------------------

#include <cassert>
#include <iostream>
#include <mutex>
#include <random>
#include <unordered_map>

//-----------------------------------------------------------------------------

const int MAX_M = 4, MAX_N = 12;

//-----------------------------------------------------------------------------

template<typename T> T ackermann1(T m, T n)
{
	if (m == 0) return n + 1;
	if (n == 0) return ackermann1(m - 1, 1);
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
		if (m == 0) solution[m][n] = n + 1;
		else if (n == 0) solution[m][n] = ackermann2(m - 1, 1);
		else solution[m][n] = ackermann2(m - 1, ackermann2(m , n - 1));
	}

	return solution[m][n];
}

//-----------------------------------------------------------------------------

template<typename T> T ackermann3(T m, T n)
{
	static std::unordered_map<T, std::unordered_map<T, T>> solution;

	auto exists_m = solution.find(m);
	if (exists_m != solution.end())
	{
		auto exists_n = exists_m->second.find(n);
		if (exists_n != exists_m->second.end())
		{
			return exists_n->second;
		}
		else
		{
			if (m == 0) (exists_m->second)[n] = n + 1;
			else if (n == 0) (exists_m->second)[n] = ackermann3(m - 1, 1);
			else (exists_m->second)[n] = ackermann3(m - 1, ackermann3(m , n - 1));
		}
	}
	else
	{
		if (m == 0) solution[m][n] = n + 1;
		else if (n == 0) solution[m][n] = ackermann3(m - 1, 1);
		else solution[m][n] = ackermann3(m - 1, ackermann3(m , n - 1));
	}

	return solution[m][n];
}

//-----------------------------------------------------------------------------

template<typename T> T ackermann4(T m, T n)
{
	static const T M = MAX_M, N = 1 << (MAX_M + MAX_N);
	static T solution[M][N] = {{0}};
	
	assert(m < M && n < N);
	
	if (!solution[m][n])
	{
		if (m == 0)
			solution[m][n] = n + 1;
		else if (n == 0)
			solution[m][n] = ackermann4(m - 1, 1);
		else
			solution[m][n] = ackermann4(m - 1, ackermann4(m, n - 1));
	}
	
	return solution[m][n];
}

//-----------------------------------------------------------------------------

template<typename T> T ackermann5(T m, T n)
{
	static std::once_flag flag;
	std::call_once(flag, [&]{ ackermann4(MAX_M - 1, MAX_N - 1); });
	
	return ackermann4(m, n);
}

//-----------------------------------------------------------------------------

template<typename F> void test(F& f)
{
	std::mt19937_64 gen(0);
	
	for (int i = 0; i < 512; ++i)
		f(gen() % MAX_M, gen() % MAX_N);
}

//-----------------------------------------------------------------------------

int main()
{
	test(ackermann1<int>);
	test(ackermann2<int>);
	test(ackermann3<int>);
	test(ackermann4<int>);
	test(ackermann5<int>);
}
//-----------------------------------------------------------------------------
