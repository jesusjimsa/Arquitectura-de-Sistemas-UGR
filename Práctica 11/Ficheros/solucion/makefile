SHELL = /bin/bash

SRC = $(sort $(wildcard *.c *.cc))
EXE = $(basename $(SRC))
DAT = $(EXE:=.dat)
LIN = $(EXE:=.lin)
LOG = $(EXE:=.log)

CFLAGS = -I. -march=native -O3 -pthread --std=c11 -Wall -Wl,--no-as-needed
CXXFLAGS = $(CFLAGS:c11=c++17)
LDFLAGS  = -lpthread -lrt

default: stat

all: sort

clean:
	-rm -fv $(DAT) $(EXE) $(LIN) $(LOG) core* *~
	-find -mindepth 2 -maxdepth 2 -name makefile -execdir make $@ \;

key:
	@printf '%77s\n' | tr ' ' '-'; \
	echo "nºlec    = número de total de lecturas (siempre correctas)"; \
	echo "nºesc    = número de total de escrituras"; \
	echo "total    = lecturas + escrituras correctas"; \
	echo "cc       = condiciones de carrera = escrituras - escrituras correctas"; \
	echo "real     = tiempo real transcurrido"; \
	echo "user     = tiempo de usuario"; \
	echo "sys      = tiempo de sistema"; \
	echo "u+s      = user + sys"; \
	echo "ratio    = total / (u + s)"; \
	printf '%77s\n' | tr ' ' '-'

stat: $(EXE)
	@function lpad { printf "%$$(( $$2 - $${#1} ))s$$1"; }; \
	function pretty_print \
	{ \
		pad=14; \
		for j in "$$@"; do \
			lpad "$$j" $$pad; \
			pad=7; \
		done; \
		echo; \
	}; \
	make -s key; \
	pretty_print programa nºlec nºesc total cc real user sys u+s ratio; \
	printf '%77s\n' | tr ' ' '-'; \
	for i in $(LIN); do \
		make -s $$i; \
		pretty_print $$(<$$i); \
	done; \
	printf '%77s\n' | tr ' ' '-'

sort: stat
	@function lpad { printf "%$$(( $$2 - $${#1} ))s$$1"; }; \
	function pretty_print \
	{ \
		pad=14; \
		for j in "$$@"; do \
			lpad "$$j" $$pad; \
			pad=7; \
		done; \
		echo; \
	}; \
	declare -a K=(2 3 4 5 9 10); \
	declare -a F=('nºlec' 'nºesc' 'total' 'cc' 'u+s' 'ratio'); \
	declare -a R=('-r' '-r' '-r' '-r' '-s' '-r'); \
	for (( i=0; i<$${#K[@]}; ++i )); do \
		echo "ordenado según $${F[$$i]}:"; \
		printf '%77s\n' | tr ' ' '-'; \
		while read line; do \
			declare -a l=($$line); \
			pretty_print $${l[@]}; \
		done < <(cat $(LIN) | sort -k $${K[$$i]} -n $${R[$$i]}); \
		printf '%77s\n' | tr ' ' '-'; \
	done

%.dat %.log: %
	-@/usr/bin/time -f "%e \t%U \t%S" -o $*.dat ./$< > $*.log 2> /dev/null

%.lin: %.dat %.log
	-@l=$$(sed 's/0/ \n0 \n/g' $*.log | grep '0' | wc -l); \
	e=$$(sed 's/a/ \na \n/g' $*.log | grep 'a' | wc -l); \
	ec=$$(grep -e '^abcdefghij$$' $*.log | wc -l); \
	(( le = l + ec )); \
	(( cc = e - ec )); \
	r=$$(cat $*.dat | cut -f 1); \
	u=$$(cat $*.dat | cut -f 2); \
	s=$$(cat $*.dat | cut -f 3); \
	us=$$(bc -lq <<< "$$u + $$s" 2> /dev/null); \
	t=$$(bc -lq <<< "$$le/$$us"); \
	us=$$(printf "%.2f" $${us/./,}); \
	t=$$(printf "%.0f" $${t/./,}); \
	echo $* $$l $$e $$le $$cc $$r $$u $$s $$us $$t | sed 's/Command terminated by signal . //g' > $@

n%: $(SRC)
	-@n=$@; \
	for i in $^; do \
		sed "s/const unsigned N = [^;]*;/const unsigned N = $${n:1};/" -i $$i; \
	done; \
	find -maxdepth 2 -mindepth 2 -name makefile -execdir make $@ \;

.PRECIOUS: $(DAT) $(LIN) $(LOG)
.PHONY: all clean default sort stat

