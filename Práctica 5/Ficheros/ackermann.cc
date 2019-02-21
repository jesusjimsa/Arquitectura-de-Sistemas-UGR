#include <iostream>

template<typename T> T ackermann(T m, T n)
{
	if (m == 0) return n + 1;
	if (n == 0) return ackermann(m - 1, 1);
	return ackermann(m - 1, ackermann(m , n - 1));
}

int main()
{
	for (int m = 0; m < 4; ++m)
		for (int n = 0; n < 14; ++n)
			std::cout << "ackermann(" << m << ", " << n << ") = " 
			          << ackermann(m, n) << std::endl;
}
