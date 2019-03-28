###############################################################################

.ONESHELL:

###############################################################################

ATT = $(EXE:=.att)
CAC = $(EXE:=.cache)
DAT = $(EXE:=.dat)
EXE = $(basename $(SRC))
LOG = $(EXE:=.log) $(EXE:=.log2)
OLD = $(DAT:=.old)
SRC = $(wildcard *.cc)

###############################################################################

CXXFLAGS = -O3 -std=c++17 -Wall # -march=native --sanitize=address
LDFLAGS += -Wl,--no-as-needed

###############################################################################

all: $(ATT)

exe: $(EXE)

clean:
	-rm -f $(ATT) $(CAC) $(DAT) $(EXE) $(LOG) $(OLD) {cache,call}grind.out.* {vg,}core.* *~

sm: selfmod
	(echo 2; echo 3) | ./$<

###############################################################################

%.att: %
	objdump -CdS $< > $@

%.cache: %.log
	cg_annotate $<
	cg_annotate --auto=yes $< $*.cc

%.dat: %
#	sudo sh -c 'echo -1 > /proc/sys/kernel/perf_event_paranoid'
	perf record --call-graph dwarf --freq=max -o $@ -- ./$<
#	perf record --call-graph dwarf -o $@ -- ./$<

%.call: %.log2
	kcachegrind $<

%.log: %
	valgrind --cachegrind-out-file=$@ --tool=cachegrind ./$<

%.log2: %
	valgrind --branch-sim=yes --cacheuse=yes --callgrind-out-file=$@ --cache-sim=yes --collect-jumps=yes --demangle=yes --dump-instr=yes --instr-atstart=yes -q --tool=callgrind --trace-jump=yes ./$<

%.perf: %.dat
	perf report -i $<

###############################################################################

ackermann: CXXFLAGS+=-pthread
bug: CXXFLAGS+=-Wno-sign-compare
facil2: CXXFLAGS+=-fno-inline
fib: CXXFLAGS+=-pthread
ijk: CXXFLAGS+=-fno-inline
selfmod:  CXXFLAGS+=-fno-inline
%-etal: CXXFLAGS+=-fopt-info

###############################################################################

.PHONY: all clean exe sm
.PRECIOUS: $(DAT) $(LOG)
.NOEXPORT:

###############################################################################

