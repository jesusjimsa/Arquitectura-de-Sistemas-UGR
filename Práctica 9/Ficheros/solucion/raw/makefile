SHELL = /bin/bash
.ONESHELL:

SRC = $(sort $(wildcard *.c *.cc))
EXE = $(basename $(SRC))
ATT = $(EXE:=.att)
DAT = $(EXE:=.dat)
LOG = $(EXE:=.log)
ST  = $(EXE:=.st)

CFLAGS = -march=native -O3 -pthread -Wall  # -fno-inline-functions -g
CXXFLAGS = $(CFLAGS) --std=c++14
LDFLAGS = -Wl,--no-as-needed

all: stat

att: $(ATT)

clean:
	-rm -fv $(ATT) $(DAT) $(EXE) $(LOG) $(ST) core.* *~
	-find -mindepth 2 -iname 'makefile' -execdir make $@ \;

sort: stat
	@declare -a N=(2 3 4 5 9 10); \
	declare -a F=('bien' 'mal' 'total' 'hebras' 'tiempo' 'ratio'); \
	declare -a R=('-r' '-r' '-r' '-r' '-s' '-r'); \
	make -s $(firstword $(ST)) >& /dev/null; \
	for (( i=0; i<$${#N[@]}; ++i )); do \
		echo; \
		echo "ordenado según $${F[$$i]}:"; \
		printf '%77s\n' | tr ' ' -; \
		head -n 1 $(firstword $(ST)); \
		printf '%77s\n' | tr ' ' -; \
#		$(MAKE) stat | grep -v ':' | egrep -w `echo $(EXE) | tr ' ' '|'` | sort -k $${N[$$i]} -n $${R[$$i]} | head -n 10; \
#		$(MAKE) stat | grep -v ':' | egrep -w `echo $(EXE) | tr ' ' '|'` | sort -k$${N[$$i]} -n $${R[$$i]}; \
		make stat | grep -v ':' | egrep -w `echo $(EXE) | tr ' ' '|'` | sort -h -k10,10 -r | sort -k$${N[$$i]},$${N[$$i]} -n $${R[$$i]} -s; \
		printf '%77s\n' | tr ' ' -; \
	done; \

stat: $(EXE)
	@printf '%77s\n' | tr ' ' -; \
	echo 'bien  : número de mensajes correctos'; \
	echo 'mal   : número de mensajes incorrectos'; \
	echo 'total : bien + mal'; \
	echo 'hebras: número de hebras que han impreso al menos un mensaje'; \
	echo 'real  : tiempo de pared en segundos'; \
	echo 'user  : tiempo de usuario en segundos'; \
	echo 'sys   : tiempo de sistema en segundos'; \
	echo 'tiempo: user + sys'; \
	echo 'ratio : bien / tiempo --> número de mensajes correctos por segundo'; \
	printf '%77s\n' | tr ' ' -; \
	make -s $(firstword $(ST)); \
	head -n 1 $(firstword $(ST)); \
	printf '%77s\n' | tr ' ' -; \
	for i in $(ST); do \
		make -s ./$$i >& /dev/null; \
		tail -n 1 $$i; \
	done; \
	printf '%77s\n' | tr ' ' -; \

%.att: %
	objdump -C -d -S $< > $@

%.dat %.log: %
	@/usr/bin/time -f "%e\t%U\t%S" -o "./$*.dat" "./$*" 2> /dev/null > "./$*.log" || true; \
	cat "./$*.dat" | grep -v "[[:alpha:]]" | grep -v "[[:alpha:]]" > "./$*.tmp"; \
	mv "./$*.tmp" "./$*.dat"

%.st: %.dat %.log
	@function lpad { printf "%$$(( $$2 - $${#1} ))s$$1"; }; \
	function pretty_print \
	{\
		pad=14;\
		for j in "$$@"; do\
			lpad "$$j" $$pad;\
			pad=7;\
		done;\
		echo;\
	};\
	if [ "$$(uname -m)" == "x86_64" ]; then \
		lid=15; \
	else \
		lid=10; \
	fi; \
#	id="$$(head -n 1 ./$*.log | tr '[]' ' ' | cut -d ' ' -f 2)"; \
#	[ -z "$$id" ] || lid=$${#id}; \
	bien=$$(grep -c -e "^\[[0-9]\{$$lid\}\]: 0123456789$$" ./$*.log); \
	total=$$(cat ./$*.log | wc -l); \
	(( mal = total - bien )); \
	hebras=$$(grep -e "^\[[0-9]\{$$lid\}\]: 0123456789$$" ./$*.log | cut -d ":" -f 1 | sort | uniq | wc -l); \
	real=$$(cat ./$*.dat | cut -f 1); \
	usuario=$$(cat ./$*.dat | cut -f 2); \
	sistema=$$(cat ./$*.dat | cut -f 3); \
	proc=$$(echo "$$usuario + $$sistema" | bc -lq 2> /dev/null); \
	e=$$(bc -lq <<< "$$bien / $$proc"); \
	pretty_print programa bien mal total hebras real user sys tiempo ratio > $@; \
	pretty_print $* $$bien $$mal $$total $$hebras $$real $$usuario $$sistema $$proc $${e%%.*} >> $@

alarm%: $(SRC)
	-@t=$@
	for i in $^; do
		sed "s/alarm([^)]*);/alarm($${t:5});/" -i $$i
	done
	find -maxdepth 2 -mindepth 2 -name makefile -execdir make $@ \;

n%: $(SRC)
	-@n=$@
	for i in $^; do
		sed "s/const int N = [^;]*;/const int N = $${n:1};/" -i $$i
	done
	find -maxdepth 2 -mindepth 2 -name makefile -execdir make $@ \;

.PHONY: all att clean sort stat
.PRECIOUS: $(DAT) $(LOG) $(ST)
.NOEXPORT:

