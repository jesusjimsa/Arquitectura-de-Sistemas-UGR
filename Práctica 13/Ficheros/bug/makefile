SHELL = /bin/bash
.ONESHELL:

DIR  = $(sort $(shell find -mindepth 1 -maxdepth 1 -type d))
SRC  = $(sort $(wildcard *.cc))
EXE  = $(basename $(SRC))
ATT  = $(EXE:=.att)
DAT  = $(EXE:=.dat)
LOG  = $(EXE:=.log)
PERF = $(EXE:=.perf)
TIM  = $(EXE:=.tim)

CXXFLAGS = -fgnu-tm -march=native -mcx16 -O3 -pthread --std=c++14 -Wall stack.h
LDLIBS += -latomic
LDFLAGS += -Wl,--no-as-needed

default: $(ATT) test

comp: $(DIR)
	@function lpad { printf "%$$(( 9 - $${#1} ))s$$1"; }; \
	function pretty_print { lpad "$$1"; shift; (( $$# > 0 )) && pretty_print "$$@" || echo; }; \
	function f { \
	printf '%81s\n' | tr ' ' '-'; \
	pretty_print "$$1". push pop sum real user system u+s kop/sec; \
	printf '%81s\n' | tr ' ' '-'; \
	for i in $^; do \
		msg=$$(make -C $$i -s test | grep " $$1 "); \
		echo "$$(lpad $$i)$${msg:9}"; \
	done 2> /dev/null; \
	}; \
	f sec; \
	f par; \
	printf '%81s\n' | tr ' ' '-'

check: $(DIR)
	@declare -A bug=(); \
	for i in $^; do \
		make -C $$i -s par; \
		bug[$$i]=0; \
	done; \
	for (( j=1; j<=100; ++j)); do \
		for i in $^; do \
			$$i/par || (( ++bug[$$i] )); \
		done &> /dev/null ; \
		echo -n "bugs[$$j]:"; \
		for i in $^; do \
			echo -n " $$i:$${bug[$$i]}"; \
		done; \
		echo; \
	done

clean:
	-rm -fv $(ATT) $(DAT) $(EXE) $(LOG) $(PERF) $(TIM) core.* *~
	-find -mindepth 2 -iname 'makefile' -execdir make $@ \;

test: $(filter-out visual,$(EXE))
	@function lpad { printf "%$$(( 9 - $${#1} ))s$$1"; }; \
	function pretty_print { lpad "$$1"; shift; (( $$# > 0 )) && pretty_print "$$@" || echo; }; \
	printf '%81s\n' | tr ' ' '-'; \
	pretty_print $$(lpad $$(basename $$PWD)) push pop sum real user system u+s kop/sec; \
	printf '%81s\n' | tr ' ' '-'; \
	for i in $^; do \
		make -s ./$$i.log ./$$i.tim; \
		p1=$$(cat ./$$i.log | cut -d ' ' -f 1); \
		p2=$$(cat ./$$i.log | cut -d ' ' -f 2); \
		t=$$(bc -lq <<< "$$p1 + $$p2"); \
		r=$$(cat ./$$i.tim | cut -d ' ' -f 1); \
		u=$$(cat ./$$i.tim | cut -d ' ' -f 2); \
		s=$$(cat ./$$i.tim | cut -d ' ' -f 3); \
		us=$$(bc -lq <<< "$$u + $$s"); \
		e=$$(bc -lq <<< "$$t / $$us / 1000.0"); \
		pretty_print $$i $$p1 $$p2 $$t $$r $$u $$s $$us $${e%%.*}; \
	done; \
	printf '%81s\n' | tr ' ' '-'; \

%: stack.h %.cc

%.att: %
	objdump -C -d $< > $@

%.dat: %
	perf record --call-graph dwarf -g -o $@ -- ./$<

%.log %.tim: %
	$$(/usr/bin/time -f "%e %U %S" -o $*.tim -- ./$< > $*.log 2> /dev/null) &> /dev/null
	for i in $*.log $*.tim; do
		grep -v '[[:alpha:]]' $$i > /tmp/$$
		mv /tmp/$$ $$i
	done
	if [ ! -s $*.log ]; then
		echo '0 0' > $*.log
	fi
	if [ ! -s $*.tim ]; then
		echo '0 0 0' > $*.tim
	fi

%.perf: %.dat
	perf report -g -i $<

.PRECIOUS: $(DAT) $(EXE)
.PHONY: all check clean comp default test $(PERF)

#	function pretty_print \
#	{ \
#		for j in "$$@"; do \
#			if [ "$$j" == "$$1" ]; then \
#				lpad "$$j" 10; \
#			else \
#				lpad "$$j"  8; \
#			fi; \
#		done; \
#		echo; \
#	}; \

