#include <iostream>

using namespace std;

int main()
{
	auto f = []{ cout << "hola, mundo!\n"; };
	f();
}
