###############################################################################

SHELL = bash
.ONESHELL:

###############################################################################

CXXFLAGS = -march=native -O3 -pthread -std=c++14 -Wall
LDFLAGS = -Wl,--no-as-needed
LDLIBS = -lrt

###############################################################################

ATT = $(EXE:=.att)
SRC = $(sort $(wildcard *.cc))
EXE = $(basename $(SRC))
DAT = $(EXE:=.dat)
LOG = $(EXE:=.log)
VER = $(EXE:=.ver)

###############################################################################

all: $(EXE) clave $(VER)
	@printf '%60s\n' | tr ' ' -

att: $(ATT)

clave:
	@printf '%60s\n' | tr ' ' -
	echo -e "clave:\tprograma = tipo de paso de mensajes"
	echo -e "\tmensajes = pings + pongs"
	echo -e "\t  tiempo = tiempo total en ms"
	echo -e "\t   ratio = suma / tiempo"
	printf '%60s\n' | tr ' ' -
	echo -e "          programa      mensajes      tiempo       ratio"
	printf '%60s\n' | tr ' ' -

clean:
	-find -maxdepth 2 -mindepth 2 -name makefile -execdir make $@ {} \;
	-rm -fv -rf $(ATT) $(DAT) $(EXE) $(LOG) {vg,}core.* perf.data *~

ratio: clave
	@$(MAKE) -s $(VER) | sort -h -k 4 -r
	printf '%60s\n' | tr ' ' -

mensajes: clave
	@$(MAKE) -s $(VER) | sort -h -k 2 -r
	printf '%60s\n' | tr ' ' -

tiempo: clave
	@$(MAKE) -s $(VER) | sort -h -k 3
	printf '%60s\n' | tr ' ' -

###############################################################################

%.att: %
	objdump -CdS $< > $@

%.dat %.log: %
	@LANG=en perf stat ./$< 1> $*.log 2> $*.dat

%.ver: %.dat %.log
	@function lpad { printf "%$$(( $$2 - $${#1} ))s$$1"; }
	function pretty_print
	{
		fill=20
		for j in "$$@"; do
			lpad "$$j" $$fill
			fill=12
		done
		echo
	}
	pings=`grep 'ping' $*.log | grep -o '[[:digit:]]*'`
	pongs=`grep 'pong' $*.log | grep -o '[[:digit:]]*'`
	(( msg = pings + pongs ))
	time=$$(grep task-clock $*.dat | tr -s ' ' | cut -d ' ' -f 2)
	ratio=$$(bc -l <<< "scale=2; $$msg/$$time" 2> /dev/null)
	pretty_print $* $$msg $$time $$ratio

###############################################################################

.PHONY: all att clave clean 
.PRECIOUS: $(LOG) $(DAT)
.NOEXPORT:

###############################################################################

