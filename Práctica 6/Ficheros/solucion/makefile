SHELL = /bin/bash

SRC = $(wildcard *.c *.cc)
EXE = $(basename $(SRC))
DAT = $(EXE:=.dat)
GP  = $(EXE:=.gp)
SVG = $(EXE:=.svg)
PNG = $(EXE:=.png)

CFLAGS   = -march=native -O3 -pthread -std=c11 -Wall -Wl,--no-as-needed # -fno-inline -ggdb
CXXFLAGS = $(CFLAGS:c11=c++14)
LDFLAGS  = -lboost_program_options -lrt

THREADS = 16
N       = 1000

default: $(EXE)

all: $(PNG)
	-find -mindepth 2 -iname 'makefile' -execdir make \;

clean:
	-rm -fv $(DAT) $(EXE) $(GP) $(PNG) $(SVG) *~ core.* *.log callgrind.out.* gmon.out perf.data*
	-find -mindepth 2 -iname 'makefile' -execdir make $@ \;

perf: matrix
	perf record --call-graph dwarf -- ./matrix -n 700
	perf report -g --no-children

stat: prod.escalar.ijk prod.escalar.ikj
	for i in $^; do perf stat ./$$i; done

val: $(EXE)
	n=256; \
	for (( p=1 ; p<=$(THREADS) ; p*=2 )); do \
		echo "valgrind --> matrix $${n}x$$n $$p"; \
		valgrind --demangle=yes --dump-instr=yes --tool=callgrind --trace-jump=yes ./matrix $$n $$n $$p; \
		mv callgrind.out.* matrix-$${n}x$${n}-$${p}.log; \
	done
	echo "ahora usa kcachegrind con... " *.log

matrix: matrix.h matrix.cc

%.dat: %
	@for (( n=100 ; n<=$(N) ; n+=100 )); do \
		echo -n $$n; \
		for (( t=1; t<=$(THREADS); t*=2 )); do \
			echo -n " $$(./$* -n $$n -t $$t | tail -1 | cut -d ' ' -f 2)"; \
		done; \
		echo; \
	done > >(tee $@)

%.gp: %.dat
	echo -n "\
		set terminal svg; \
		set out 'matrix.svg'; \
		set key top left; \
		set xlabel 'matrix size (NxN)'; \
		set ylabel 'time (in seconds)'; \
		plot" > $@
	for (( p=1, u=2 ; p<=$(THREADS) ; p*=2, u+=1 )); do \
		echo -n " 'matrix.dat' u 1:(\$$$$u / 1e9) t '$$p' w lp"; \
		if [ "$$p" -lt "$(THREADS)" ]; then \
			echo -n ","; \
		fi; \
	done >> $@

%.svg: %.gp
	gnuplot $<

%.png: %.svg
	convert $<  $@

.PHONY: all clean default perf stat val
.PRECIOUS: $(DAT) $(GP) $(PNG) $(SVG)

