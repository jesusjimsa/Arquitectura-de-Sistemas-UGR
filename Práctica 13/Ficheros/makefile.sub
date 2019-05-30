###############################################################################

.ONESHELL:

###############################################################################

ATT = $(EXE:=.att)
EXE = $(basename $(SRC))
SRC = $(wildcard *.cc)

###############################################################################

CXXFLAGS = -fgnu-tm -I.. -march=native -O3 -std=c++14 -pthread -Wall
LDFLAGS = -L..
LDLIBS = -Wl,--no-as-needed -ldl -lrpmallocwrap

###############################################################################

all: check

att: $(ATT)

clean:
	-rm -fv $(ATT) $(EXE) core.* *~

check: stack
	@if ! nm -C ./$< | grep -q rpmalloc; then
		echo 'rpmalloc lib NOT detected!'
		exit 1
	fi

exe: $(EXE)

###############################################################################

%.att: %
	objdump -Cd $< > $@

%.mc: %
	valgrind --leak-check=full -s --show-leak-kinds=all ./$<

###############################################################################

.PHONY: all att clean check exe

###############################################################################

