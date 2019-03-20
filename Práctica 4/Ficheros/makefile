ATT = $(EXE:=.att)
EXE = $(basename $(SRC))
SRC = $(wildcard *.c *.cc)

CFLAGS = -march=native -g -Os -pthread -std=c11 -Wall
CXXFLAGS = $(CFLAGS:c11=c++11)

all: $(EXE)

att: $(ATT)

clean:
	-rm -fv $(ATT) $(EXE) *~ callgrind.out.* perf.data *.log
	-rm -rf *.dSYM

exe: $(EXE)

%.att: %
	objdump -Cd $< > $@

%.log: %
	valgrind --tool=callgrind --branch-sim=yes --cache-sim=yes --callgrind-out-file=$*.log --collect-bus=yes --collect-jumps=yes --dump-instr=yes --dump-line=yes -- ./$<

%.cg: %.log
	kcachegrind $<

.PHONY: all att clean

