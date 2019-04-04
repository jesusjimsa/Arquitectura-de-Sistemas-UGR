#include <cstdio>

const int N = 1000;

void work(int begin, int end){
	for (int i = begin; i < end; ++i){
		// open bw+
		std::FILE *f = std::tmpfile();
		
		// write
		std::fputs("Hello, world", f);
		
		// rewind
		rewind(f);
		
		// read
		char buffer[32];
		std::fgets(buffer, sizeof buffer, f);
	}
}

