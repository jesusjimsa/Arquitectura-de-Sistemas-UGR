#include <iostream>
#include "stack.h"

template<class T> std::ostream& operator<<(std::ostream& os, stack<T>& s)
{
	auto n = s.pop();
	if (n != nullptr)
	{
		os << n->data << ' ' << s;
		s.push(n);
	}
	return os;
}

int main()
{
	const int N = 10;

	stack<int> s;

	for (int i = 0; i < N; ++i)
	{
		s.push(new stack<int>::node{nullptr, i});
		std::cout << "s = " << s << std::endl;
	}

	while (s.pop() != nullptr)
		std::cout << "s = " << s << std::endl;
}
