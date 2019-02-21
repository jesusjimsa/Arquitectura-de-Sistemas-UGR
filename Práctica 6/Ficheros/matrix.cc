//-----------------------------------------------------------------------------
// matrix.cc
// info: http://www.boost.org/doc/libs/1_55_0/doc/html/program_options.html
//       http://www.radmangames.com/programming/how-to-use-boost-program_options
//-----------------------------------------------------------------------------

#include <chrono>
#include <functional>
#include <iostream>
#include <random>
#include <sstream>
#include <stdexcept>

#include <boost/program_options.hpp>

#include "matrix.h"

namespace po = boost::program_options;

//-----------------------------------------------------------------------------

unsigned N = 10;      // number of rows and columns
unsigned THREAD = 1;  // number of threads
bool verbose = false; // verbose output

//-----------------------------------------------------------------------------

void work()
{
	std::default_random_engine generator(N);
	std::uniform_int_distribution<int> distribution(0, 9);
	auto rng = std::bind(distribution, generator);

	auto t1 = std::chrono::high_resolution_clock::now();

	matrix<int> a(N);
	a.random(rng);

	if (verbose)
		std::cout << "a = " << std::endl << a;

	matrix<int> t(a);
	t.transpose();

	if (verbose)
		std::cout << "t = " << std::endl << t;

	matrix<int> s(a);
	s *= s;

	if (verbose)
		std::cout << "s = " << std::endl << s;

	matrix<int> o(N, 1);

	if (verbose)
		std::cout << "o = " << std::endl << o;

	a = a * t + s - o;

	auto t2 = std::chrono::high_resolution_clock::now();

	if (verbose)
		std::cout << "a = " << std::endl << a << std::endl;

	std::cout << "tiempo: " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() 
	          << " ns" << std::endl;
	
}

//-----------------------------------------------------------------------------

void parser(int argc, char *argv[])
{
	po::options_description desc("program options");

	desc.add_options()
		("help,h", "help message")
		("number,n", po::value<unsigned>(&N)->default_value(10), "number of rows and columns")
		("threads,t", po::value<unsigned>(&THREAD)->default_value(1), "number of threads ")
		("verbose,v", "verbose output")
	;

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	if (vm.count("help"))
		throw desc;

	if (vm.count("verbose"))
		verbose =  true;
	else
		verbose = false;
}

//-----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
	try
	{
		parser(argc, argv);
		work();
	}
	catch (po::options_description& desc)
	{
		std::cout << desc;
	}
	catch (std::exception& e)
	{
		std::cerr << argv[0] << ": " << e.what() << std::endl;
		return 1;
	}
}

//-----------------------------------------------------------------------------

// Local Variables:
// mode:C++
// End:
