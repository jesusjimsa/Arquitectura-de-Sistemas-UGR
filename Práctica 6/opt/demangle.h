//------------------------------------------------------------------------
// demangle.h - (C) Gustavo Romero López 2018 - GPLv3
//------------------------------------------------------------------------

#ifndef DEMANGLE_H
#define DEMANGLE_H

//------------------------------------------------------------------------

#include <cxxabi.h>  // abi::__cxa_demangle
#include <cstdlib>   // free
#include <memory>    // unique_ptr
#include <stdexcept> // runtime_error
#include <string>    // string
#include <typeinfo>  // typeid

//------------------------------------------------------------------------

#if __cplusplus < 201103L
#error C++11 compiler required by std::unique_ptr usage
#endif

//------------------------------------------------------------------------

namespace ec
{
	std::string demangle(const char* name)
	{
		int status = 0;
		// enable c++11 by passing the flag -std=c++11 to g++
		std::unique_ptr<char, void(*)(void*)> result
		{
			abi::__cxa_demangle(name, nullptr, nullptr, &status), 
			std::free
		};
		
		switch(status)
		{
			case  0: return result.get(); break;
			case -1: throw std::runtime_error("a memory allocation failure occurred"); break;
//			case -2: throw std::runtime_error("mangled name is not a valid name under the C++ ABI mangling rules"); break;                            // error???
/*			case -2: return name; break;                        // mangled name???*/
/*			default: throw std::runtime_error("invalid argument"); break;*/
		}
		
		return name;
	}
	
	template<class T> std::string demangle(const T& t = T())
	{
		return demangle(typeid(T).name());
	}

} // namespace ec

//------------------------------------------------------------------------

#endif // DEMANGLE_H
