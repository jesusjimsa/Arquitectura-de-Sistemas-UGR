#ifndef tagged_h
#define tagged_h 1

#include <cstddef>

//-----------------------------------------------------------------------------
// tagged
//-----------------------------------------------------------------------------

namespace tagged
{
//-----------------------------------------------------------------------------
// tagged::pointer
//-----------------------------------------------------------------------------

template <typename T> struct pointer
{
	pointer(T* p = nullptr, std::size_t t = 0): ptr(p), tag(t) {}

	T* operator->() const { return ptr; }

	operator T* () const { return ptr; }

	operator bool() const { return ptr != nullptr; }

	T*          ptr;
	std::size_t tag;
};

} // tagged::pointer

#endif // tagged_h
