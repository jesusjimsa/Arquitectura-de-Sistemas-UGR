SHELL = /bin/bash

ATT = $(EXE:=.att) $(shell echo consumidor-{{0..3},g,s}.att productor-{{0..3},g,s}.att)
DAT = $(REO:=.dat)
EXE = $(basename $(SRC))
LOG = $(REO:=.log)
REO = $(sort $(filter reorder%,$(EXE)))
SRC = $(wildcard *.cc)
TXT = $(REO:=.txt)

CXXFLAGS = -g -march=native -O3 -pthread -Wall # -fpie -pie

all: att stat

att: $(ATT)

clean:
	-rm -fv $(ATT) $(DAT) $(EXE) $(LOG) $(TXT) *~

exe: $(EXE)

stat: $(REO)
	@printf '%80s\n' | tr ' ' '-'; \
	echo "key:"; \
	echo -e "\t r1=r2=0: number of reorders detected"; \
	echo -e "\t iter   : iterations of the program"; \
	echo -e "\t real   : real time in seconds"; \
	echo -e "\t user   : user time in seconds"; \
	echo -e "\t system : system time in seconds"; \
	echo -e "\t u+s    : user time + system time"; \
	echo -e "\t rate   : iterations per second"; \
	printf '%80s\n' | tr ' ' '-'; \
	echo "          program  r1=r2=0     iter     real     user   system      u+s     rate"; \
	printf '%80s\n' | tr ' ' '-'; \
	for i in $(TXT); do $(MAKE) -s $$i; cat $$i; done; \
	printf '%80s\n' | tr ' ' '-'

ipc-0: CXXFLAGS:=$(CXXFLAGS:-O3=-O0)
ipc-1: CXXFLAGS:=$(CXXFLAGS:-O3=-O1)
ipc-2: CXXFLAGS:=$(CXXFLAGS:-O3=-O2)
ipc-3: CXXFLAGS:=$(CXXFLAGS:-O3=-O3)
ipc-g: CXXFLAGS:=$(CXXFLAGS:-O3=-Og)
ipc-s: CXXFLAGS:=$(CXXFLAGS:-O3=-Os)

consumidor-%.att: ipc-%
	gdb -batch -ex "file $<" -ex "disass consumidor" | c++filt | sed 's/0x0000000000/0x/g' > $@

productor-%.att: ipc-%
	gdb -batch -ex "file $<" -ex "disass productor" | c++filt | sed 's/0x0000000000/0x/g' > $@

%.att: %
	objdump -C -d $< > $@

%.dat %.log: %
	@/usr/bin/time -f "%e\n%U\n%S" -o "./$<.dat" "./$<" 2> /dev/null > "./$<.log"

%.txt: %.dat %.log makefile
	@pad=17; \
	lpad() { printf "%$$(( $$pad - $${#1} ))s$$1"; pad=9; }; \
	print() { lpad "$$1"; shift; (( $$# > 0 )) && print "$$@" || echo; pad=17; }; \
	reorders=$$(tail -1 "./$*.log" | cut -d ' ' -f 1); \
	iteraciones=$$(tail -1 "./$*.log" | cut -d ' ' -f 5); \
	real=$$(sed '1q;d' "./$*.dat"); \
	usuario=$$(sed '2q;d' "./$*.dat"); \
	sistema=$$(sed '3q;d' "./$*.dat"); \
	total=$$(bc -lq <<< "$$usuario + $$sistema"); \
	rate=$$(bc -q <<< "$$iteraciones/$$total"); \
	print $* $$reorders $$iteraciones $$real $$usuario $$sistema $$total $$rate > $@

.PRECIOUS: $(DAT) $(LOG) $(TXT)
.PHONY: all att clean exe stat

