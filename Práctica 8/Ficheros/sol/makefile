SHELL = /bin/bash
.ONESHELL:

SRC = $(wildcard *.c *.cc)
EXE = $(basename $(SRC))

CFLAGS = -march=native -O3 -pthread --std=c11 -Wall
CXXFLAGS = $(CFLAGS:c11=c++14)

all: $(EXE) test

clean:
	-rm $(EXE) *~
	-find -mindepth 2 -maxdepth 2 -name makefile -execdir make $@ \;

test: $(sort $(filter-out alarma% id,$(EXE)))
	@for i in $^; do
		echo -n "$$i: "
		perf stat -r 3 -- ./$$i |& grep 'task-clock' | tr -s ' '
		./$$i | grep -v Temporizador | sort | uniq -c
	done

.PHONY: all clean test

