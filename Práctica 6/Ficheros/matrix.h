//-----------------------------------------------------------------------------
// matrix.h
//-----------------------------------------------------------------------------

#ifndef MATRIX_H
#define MATRIX_H

//-----------------------------------------------------------------------------

#include <iostream>
#include <vector>

//-----------------------------------------------------------------------------

extern unsigned THREAD; // number of threads from matrix.cc

//-----------------------------------------------------------------------------

template<typename _t>
std::ostream& operator<<(std::ostream& os, const std::vector<_t>& v)
{
	os << '<';
	for (auto i: v)
		os << i << ' ';
	return os << '>';
}

//-----------------------------------------------------------------------------

template<typename _t> class matrix: public std::vector<std::vector<_t>>
{
public:
	matrix(unsigned __size = 0, _t __t = _t()): 
		std::vector<std::vector<_t>>(__size, std::vector<_t>(__size, __t)) {}

	template<class _rng> void random(_rng& __rng)
	{
		for (auto& i: *this)
			for (auto& j: i)
				j = __rng();
	}

	void transpose()
	{
		for (unsigned i = 0; i < this->size(); ++i)
			for (unsigned j = i + 1; j < this->size(); ++j)
				std::swap((*this)[i][j], (*this)[j][i]);
	}

	matrix& operator+=(const matrix& m)
	{
		for (unsigned i = 0; i < this->size(); ++i)
			for (unsigned j = 0; j < this->size(); ++j)
				(*this)[i][j] += m[i][j];
		return *this;
	}

	matrix& operator-=(const matrix& m)
	{
		for (unsigned i = 0; i < this->size(); ++i)
			for (unsigned j = 0; j < this->size(); ++j)
				(*this)[i][j] -= m[i][j];
		return *this;
	}

	matrix& operator*=(const matrix& m)
	{
		matrix r(m.size(), 0);
		for (unsigned i = 0; i < this->size(); ++i)
			for (unsigned j = 0; j < this->size(); ++j)
				for (unsigned k = 0; k < this->size(); ++k)
					r[i][j] += (*this)[i][k] * m[k][j];
		this->swap(r);
		return *this;
	}

	friend std::ostream& operator<<(std::ostream& os, const matrix& m)
	{
		for (auto& i: m)
		{
			os << "[ ";
			for (auto& j: i)
				os << j << ' ';
			os << "]" << std::endl;
		}
		return os;
	}
};

//-----------------------------------------------------------------------------

template<typename _t>
matrix<_t> operator+(const matrix<_t>& __x, const matrix<_t>& __y)
{
	matrix<_t> __r = __x;
	__r += __y;
	return __r;
}

template<typename _t>
matrix<_t> operator-(const matrix<_t>& __x, const matrix<_t>& __y)
{
	matrix<_t> __r = __x;
	__r -= __y;
	return __r;
}

template<typename _t>
matrix<_t> operator*(const matrix<_t>& __x, const matrix<_t>& __y)
{
	matrix<_t> __r = __x;
	__r *= __y;
	return __r;
}

//-----------------------------------------------------------------------------

#endif // MATRIX_H

//-----------------------------------------------------------------------------

// Local Variables:
// mode:C++
// End:

