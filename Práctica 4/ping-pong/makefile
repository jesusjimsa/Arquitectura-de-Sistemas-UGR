###############################################################################

SHELL = bash
.ONESHELL:

###############################################################################

CXXFLAGS = -march=native -O3 -pthread -std=c++14 -Wall
LDFLAGS = -lrt

###############################################################################

SRC = $(sort $(wildcard *.cc))
EXE = $(basename $(SRC))
DAT = $(EXE:=.dat)
LOG = $(EXE:=.log)
VER = $(EXE:=.ver)

###############################################################################

default: $(EXE) clave $(VER)
	@printf '%60s\n' | tr ' ' -

clave:
	@printf '%60s\n' | tr ' ' -
	echo -e "clave:\tprograma = tipo de paso de mensajes"
	echo -e "\t    suma = pings + pongs"
	echo -e "\t   total = tiempo de usuario + tiempo de sistema"
	echo -e "\t   ratio = suma / total"
	printf '%60s\n' | tr ' ' -
	echo -e "          programa        suma       total       ratio"
	printf '%60s\n' | tr ' ' -

clean:
	-find -maxdepth 2 -mindepth 2 -name makefile -execdir make $@ {} \;
	-rm -fv -rf $(ATT) $(DAT) $(EXE) $(LOG) core.* *~

ratio:	clave
	@$(MAKE) -s $(VER) | grep -v '-' | sort -h -k 4 -r
	printf '%60s\n' | tr ' ' -

suma:	clave
	@$(MAKE) -s $(VER) | grep -v '-' | sort -h -k 2 -r
	printf '%60s\n' | tr ' ' -

total:	clave
	@$(MAKE) -s $(VER) | grep -v '-' | sort -h -k 3
	printf '%60s\n' | tr ' ' -

###############################################################################

%.dat %.log: %
	@/usr/bin/time -v ./$< 1> $*.log 2> $*.dat

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
	(( sum = pings + pongs ))
	user=`grep 'User time' $*.dat | grep -o '[[:digit:]].[[:digit:]]*'`
	system=`grep 'System time' $*.dat | grep -o '[[:digit:]].[[:digit:]]*'`
	total=`bc <<< "$$user+$$system"`
	ratio=`bc <<< "$$sum/$$total" 2> /dev/null`
	pretty_print $* $$sum $$total $$ratio

###############################################################################

.PHONY: all clave clean default
.PRECIOUS: $(LOG) $(DAT)
.NOEXPORT:

###############################################################################

