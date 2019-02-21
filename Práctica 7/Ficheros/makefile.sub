SHELL = bash
.ONESHELL:

SRC = $(sort $(wildcard *.cc))
EXE = $(basename $(SRC))

CXXFLAGS = -march=native -O3 -pthread -std=c++11 -Wall

all: $(EXE)
	@for i in $^; do 
		rm -f *.dat
		echo -n "$$i: "
		perf stat -r 5 -- ./$$i |& grep 'task-clock' | tr -s ' '
	done

clean:
	-rm -fv $(EXE) core.* *~

$(EXE): work.h

.PHONY: all clean

