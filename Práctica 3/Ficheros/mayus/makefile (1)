ASM = $(wildcard *.s)
OBJ = $(ASM:.s=.o)
BIN = $(OBJ:.o=.bin)
ATT = $(BIN:.bin=.att)

default: $(ATT) qemu

clean:
	-killall -q qemu-system-i386 || true
	-rm -fv $(ATT) $(BIN) $(OBJ) core.* *~

qemu: $(BIN)
	qemu-system-i386 -drive file=$(BIN),format=raw &> /dev/null &

%.bin:	%.o
	$(LD) --oformat binary -Ttext 0x7c00 $< -o $@

%.att: %.bin
	objdump -D -b binary -mi386 -Maddr16,data16 $< > $@

.PHONY: clean default qemu

