SHELL = /bin/bash
.ONESHELL:

SRC = $(sort $(wildcard *.cc))
EXE = $(basename $(SRC))
DAT = $(EXE:=.dat)
LOG = $(EXE:=.log)
SEE = $(EXE:=.see)

CXXFLAGS = -march=native -O3 -pthread --std=c++17 -Wall
LDFLAGS =  -Wl,--no-as-needed
#LDLIBS = -lboost_thread

default: stat

all: sort

clave: $(EXE)
	@function lpad { printf "%$$(( $$2 - $${#1} ))s$$1"; }; \
	function pretty_print \
	{ \
		pad=12; \
		for j in "$$@"; do \
			lpad "$$j" $$pad; \
			pad=8; \
		done; \
		echo; \
	}; \
	printf '%84s\n' | tr ' ' '-'; \
	echo -e "clave: una almoadilla después del nombre del programa indica error" ; \
	echo -e " \t amin: mínimo número de antes" ; \
	echo -e " \t amax: máximo número de antes"; \
	echo -e " \t dmin: mínimo número de después" ; \
	echo -e " \t dmax: máximo número de después"; \
	echo -e " \t msg : número total de mensajes"; \
	echo -e " \t user: tiempo de usuario empleado en segundos"; \
	echo -e " \t sys : tiempo del sistema consumido en segundos"; \
	echo -e " \t u+s : suma de tiempos de usuario y sistema en segundos"; \
	echo -e " \t m/t : msg / (user + sys)"; \
	printf '%84s\n' | tr ' ' '-'; \
	pretty_print "programa" "amin" "amax" "dmin" "dmax" "msg" "user" "sys" "u+s" "m/t"; \
	printf '%84s\n' | tr ' ' '-'; \

clean:
	-rm -fv $(DAT) $(EXE) $(LOG) $(SEE) perf.* core* *~
	-find -mindepth 2 -maxdepth 2 -iname makefile -execdir make $@ \;

sort: stat
	@echo 'sort by msg'; \
	printf '%84s\n' | tr ' ' '-'; \
	cat $(SEE) | sort -n -k 10 -r | sort -n -k 6 -r -s; \
	printf '%84s\n' | tr ' ' '-'; \
	echo 'sort by u+s'; \
	printf '%84s\n' | tr ' ' '-'; \
	cat $(SEE) | sort -n -k 10 -r | sort -n -k 9 -s; \
	printf '%84s\n' | tr ' ' '-'; \
	echo 'sort by m/t'; \
	printf '%84s\n' | tr ' ' '-'; \
	cat $(SEE) | sort -n -k 10 -r; \
	printf '%84s\n' | tr ' ' '-'

stat: clave
	@for i in $(SEE); do \
		$(MAKE) -s $$i; \
		cat $$i; \
	done; \
	printf '%84s\n' | tr ' ' '-'

boost: CXXFLAGS+=-lboost_system -lboost_thread

%.att: %
	objdump -C -d -S $< > $@

%.dat %.log: %
	@/usr/bin/time -f "%e \t%U \t%S" -o ./$*.dat ./$< 2> /dev/null | grep ':' > ./$*.log

%.see: %.dat %.log
	@function lpad { printf "%$$(( $$2 - $${#1} ))s$$1"; }; \
	function pretty_print \
	{ \
		pad=12; \
		for j in "$$@"; do \
			lpad "$$j" $$pad; \
			pad=8; \
		done; \
		echo; \
	}; \
	declare -a hebras=(`cat ./$*.log | cut -d ':' -f 1 | sort -n | uniq | tr ' \n' ' '`); \
	amin=`grep -c "$${hebras[0]}: antes" ./$*.log`; \
	dmin=`grep -c "$${hebras[0]}: después" ./$*.log`; \
	amax=0; \
	dmax=0; \
	msg=0; \
	for (( i=0; i<$${#hebras[@]}; ++i )); do \
		antes[$$i]=`grep -c "^$${hebras[$$i]}: antes" ./$*.log`; \
		if (( $${antes[$$i]} < amin )); then amin=$${antes[$$i]}; fi; \
		if (( $${antes[$$i]} > amax )); then amax=$${antes[$$i]}; fi; \
		despues[$$i]=`grep -c "^$${hebras[$$i]}: después" ./$*.log`; \
		if (( $${despues[$$i]} < dmin )); then dmin=$${despues[$$i]}; fi; \
		if (( $${despues[$$i]} > dmax )); then dmax=$${despues[$$i]}; fi; \
		(( msg += $${antes[$$i]} + $${despues[$$i]})); \
	done; \
	real=$$(grep -v [[:alpha:]] ./$*.dat | cut -f 1); \
	user=$$(grep -v [[:alpha:]] ./$*.dat | cut -f 2); \
	sys=$$(grep -v [[:alpha:]] ./$*.dat | cut -f 3); \
	sum=$$(echo "$$user + $$sys" | bc -lq 2> /dev/null); \
	if [ "$$sum" != "0" ]; then \
		mxt=`bc -lq <<< "$$msg / $$sum"`; \
	else \
		mxt="0"; \
	fi; \
	error="$*"; \
	if (( (amin - dmax) > 1 || (amin - dmax) < -1 )); then error="$*#"; fi; \
	pretty_print $$error $$amin $$amax $$dmin $$dmax $$msg $$user $$sys $$sum $${mxt%%.*} > $@

n%: $(SRC)
	-@n=$@
	for i in $^; do
		sed "s/const int N = [^;]*;/const int N = $${n:1};/" -i $$i
	done
	find -maxdepth 2 -mindepth 2 -name makefile -execdir make $@ \;

.PRECIOUS: $(DAT) $(LOG)
.PHONY: all clave clean default sort

