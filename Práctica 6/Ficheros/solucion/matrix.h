//-----------------------------------------------------------------------------
// matrix.h
//-----------------------------------------------------------------------------

#ifndef MATRIX_H
#define MATRIX_H

//-----------------------------------------------------------------------------

#include <cmath>
#include <future>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

//-----------------------------------------------------------------------------

extern unsigned THREAD; // number of threads from matrix.cc

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
		matrix r(m.size()), t(m);
		t.transpose();
		std::vector<std::future<void>> f;
		unsigned chunk = ceil(static_cast<float>(this->size()) / THREAD);
		for (unsigned c = 0; c < this->size(); c += chunk)
			f.push_back(std::async(std::launch::async, [&,c]
			{
				for (unsigned i = c; i < std::min(c + chunk, static_cast<unsigned>(this->size())); ++i)
					for (unsigned j = 0; j < r[i].size(); ++j)
						r[i][j] = std::inner_product((*this)[i].begin(), (*this)[i].end(), t[j].begin(), 0);
			}));
		for (auto& i: f)
			i.wait();
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

