//-----------------------------------------------------------------------------
// matrix.h
//-----------------------------------------------------------------------------

#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <iterator>
#include <numeric>

using namespace std;

//-----------------------------------------------------------------------------
// array op T
//-----------------------------------------------------------------------------

template<class T, size_t N>
array<T, N> operator+(const array<T, N>& a, const T& b){
	array<T, N> a2;

	for (size_t i = 0; i < a2.size(); ++i){
		a2[i] = a[i] + b;
	}

	return a2;
}

template<class T, size_t N>
array<T, N> operator-(const array<T, N>& a, const T& b){
	auto a2 = a;

	for (size_t i = 0; i < a2.size(); ++i){
		a2[i] -= b;
	}

	return a2;
}

template<class T, size_t N>
array<T, N> operator*(const array<T, N>& a, const T& b){
	array<T, N> a2;

	for (size_t i = 0; i < a2.size(); ++i){
		a2[i] = a[i] * b;
	}

	return a2;
}

//-----------------------------------------------------------------------------
// array
//-----------------------------------------------------------------------------

template<class T, size_t N>
T operator*(const array<T, N>& a, const array<T, N>& b){
	return inner_product(a.begin(), a.end(), b.begin(), T(0));
}

template <typename T, size_t N>
ostream& operator<<(ostream& os, const array<T, N>& a){
	os << '<';

	for_each(a.begin(), a.end(), [&](const T& t){ os << t << ' '; });

	return os << '>';
}

//-----------------------------------------------------------------------------
// matrix
//-----------------------------------------------------------------------------

template<class T, size_t R, size_t C>
using matrix = array<array<T, C>, R>;

template<class T, size_t R, size_t C>
matrix<T, R, C> operator+(const matrix<T, R, C>& m1, const matrix<T, R, C>& m2){
	matrix<T, R, C> tmp = m1;

	for (size_t i = 0; i < R; ++i){
		for (size_t j = 0; j < C; ++j){
			tmp[i][j] += m2[i][j];
		}
	}

	return tmp;
}

template<class T, size_t R, size_t C>
matrix<T, R, C> operator-(const matrix<T, R, C>& m1, const matrix<T, R, C>& m2){
	matrix<T, R, C> tmp = m1;

	for (size_t i = 0; i < R; ++i){
		for (size_t j = 0; j < C; ++j){
			tmp[i][j] -= m2[i][j];
		}
	}

	return tmp;
}

template<class T, size_t R, size_t N, size_t C>
matrix<T, R, C> operator*(const matrix<T, R, N>& m1, const matrix<T, N, C>& m2){
	matrix<T, R, C> tmp = {0};

	for (size_t i = 0; i < R; ++i){
		for (size_t k = 0; k < N; ++k){
			for (size_t j = 0; j < C; ++j){
				tmp[i][j] += m1[i][k] * m2[k][j];
			}
		}
	}

	return tmp;
}

//-----------------------------------------------------------------------------
// array op matrix
//-----------------------------------------------------------------------------

template<class T, size_t R, size_t C>
array<T, R> operator*(const matrix<T, R, C>& m,  const array<T, C>& a){
	array<T, R> tmp = {0};

	for (size_t i = 0; i < R; ++i){
		for (size_t j = 0; j < C; ++j){
			tmp[i] += m[i][j] * a[j];
		}
	}

	return tmp;
}

template<class T, size_t R, size_t C>
array<T, C> operator*(const array<T, R>& a,  const matrix<T, R, C>& m){
	array<T, C> tmp = {0};

	for (size_t k = 0; k < R; ++k){
		for (size_t j = 0; j < C; ++j){
			tmp[j] += a[k] * m[k][j];
		}
	}

	return tmp;
}

//-----------------------------------------------------------------------------

