.ONESHELL:

all: stat

clean:
	-rm -fv core.* *~
	-find -mindepth 2 -maxdepth 2 -iname makefile -execdir make $@ \;

stat: $(shell find -mindepth 1 -maxdepth 1 -type d | sort)
	@lpad() { printf "%$$(( 8 - $${#1} ))s $$1"; }
	print() { lpad "$$1"; shift; (( $$# > 0 )) && print "$$@" || echo; }
	printf '%27s\n' | tr ' ' '-'
	print version push pop
	printf '%27s\n' | tr ' ' '-'
	for d in $^; do
		make -C $$d -s stack
		declare -a a=($$($$d/stack))
		print $$d $${a[0]} $${a[1]}
	done

