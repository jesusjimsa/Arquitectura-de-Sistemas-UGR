SHELL = /bin/bash

SRC = $(wildcard *.c *.cc)
EXE = $(basename $(SRC))
LOG = sort.log
SVG = sort.svg sort.l.svg
PNG = $(SVG:.svg=.png)

CFLAGS = -march=native -Ofast -pthread -std=c11 -Wall -Wl,--no-as-needed
CXXFLAGS = $(CFLAGS:c11=c++11)

default: $(EXE)

all: $(PNG)

clean:
	$(RM) -rf $(EXE) $(LOG) $(PNG) $(SVG) core.* perf.* *~

comp: fib fib-map fib-hash fib-hash2 fib-array
	@for i in $^; do time ./$$i 46; done

list: fib-hash2
	@echo "for unsigned long long..."; \
	for ((i = 90; i < 95; ++i)); do ./$< $$i; done

perf:
	@echo "perf record --call-graph dwarf ./fib-map 93"; \
	echo "perf report -g graph --no-children --sort comm,dso,sym"

.PHONY: all clean comp default list perf

sort: CFLAGS+=-fopenmp

%.log: %
	@./$< | tee $@

%.png: %.svg
	convert -density 400 $< $@

%.svg: %.log makefile
	@gnuplot <<< "set terminal svg enhanced; \
	              set output '$@'; \
	              set key autotitle columnheader left top noenhanced; \
	              set grid; \
	              set xlabel 'size'; \
	              set logscale x 2; \
	              set ylabel 'time'; \
	              set xtics rotate; \
	              set xtics (1, 2, 4, 8, 16, 32, 64, 128, 256, 512, '1k' 1024, '2k' 2048, '4k' 4096, '8k' 8192, '16k' 16384, '32k' 32768, '64k' 65526, '128k' 131072, '256k' 262144, '512k' 524288, '1M' 1048576, '2M' 2097152, '4M' 4194304, '8M' 8388608, '16M' 16777216, '32M' 33554432, '64M' 67108864, '128M' 134217728, '256M' 268435456, '512M' 536870912, '1G' 1073741824); \
	              set ytics ('5ms' 5e6, '10ms' 10e6, '15ms' 15e6, '20ms' 20e6, '25ms' 25e6, '30ms' 30e6, '35ms' 35e6, '40ms' 40e6, '45ms' 45e6, '50ms' 50e6, '55ms' 55e6, '60ms' 60e6, '65ms' 65e6, '70ms' 70e6, '75ms' 75e6, '80ms' 80e6, '85ms' 85e6, '90ms' 90e6, '95ms' 95e6, '100ms' 100e6); \
	              plot '$<' u 1:2 w lp lc -1 ps 0.66 pt 5, \
	                   '$<' u 1:3 w lp lc 1 ps 0.66 pt 7, \
	                   '$<' u 1:4 w lp lc 2 ps 0.66 pt 9, \
	                   '$<' u 1:5 w lp lc 3 ps 0.66 pt 13"

%.l.svg: %.log makefile
	@gnuplot <<< "set terminal svg enhanced; \
	              set output '$@'; \
	              set key autotitle columnheader bottom noenhanced; \
	              set grid; \
	              set xlabel 'size'; \
	              set ylabel 'time'; \
	              set logscale x 2; \
	              set logscale y 10; \
	              set xtics rotate; \
	              set xtics (1, 2, 4, 8, 16, 32, 64, 128, 256, 512, '1k' 1024, '2k' 2048, '4k' 4096, '8k' 8192, '16k' 16384, '32k' 32768, '64k' 65526, '128k' 131072, '256k' 262144, '512k' 524288, '1M' 1048576, '2M' 2097152, '4M' 4194304, '8M' 8388608, '16M' 16777216, '32M' 33554432, '64M' 67108864, '128M' 134217728, '256M' 268435456, '512M' 536870912, '1G' 1073741824); \
	              set ytics ('1ns' 1e0, '10ns' 1e1, '100ns' 1e2, '1us' 1e3, '10us' 1e4, '100us' 1e5, '1ms' 1e6, '10ms' 1e7, '100ms' 1e8, '1s' 1e9, '10s' 1e10, '100s' 1e11); \
	              plot '$<' u 1:2 w lp lc -1 ps 0.66 pt 5, \
	                   '$<' u 1:3 w lp lc 1 ps 0.66 pt 7, \
	                   '$<' u 1:4 w lp lc 2 ps 0.66 pt 9, \
	                   '$<' u 1:5 w lp lc 3 ps 0.66 pt 13"

.PRECIOUS: $(LOG) $(SVG)
.NOEXPORT:
