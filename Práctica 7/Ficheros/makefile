SRC = $(filter-out $(wildcard server*.cc),$(wildcard *.cc))
EXE = $(basename $(SRC))

CXXFLAGS = -march=native -O3 -pthread -std=c++11 -Wall

default: $(EXE)

all:
	-find -mindepth 2 -maxdepth 2 -name makefile -execdir make \;

clean:
	-rm -fv $(EXE) *~
	-find -mindepth 2 -maxdepth 2 -name makefile -execdir make $@ \;

.PHONY: all clean default

