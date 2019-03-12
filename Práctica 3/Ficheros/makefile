default:
	find -mindepth 2 -maxdepth 2 -name makefile -execdir make \;
clean:	
	-rm -fv *~
	-killall -q qemu-system-i386 || true
	-find -mindepth 2 -maxdepth 2 -name makefile -execdir make $@ \;

.PHONY: clean default

