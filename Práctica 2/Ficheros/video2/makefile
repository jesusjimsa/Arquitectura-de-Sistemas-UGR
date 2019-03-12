ASM = $(wildcard *.s)
OBJ = $(ASM:.s=.o)
BIN = $(basename $(ASM))
ATT = $(ASM:.s=.att)

all: $(ATT) qemu

clean:
	-killall -q qemu-system-i386 || true
	-rm -fv $(ATT) $(BIN) $(OBJ) *~

debug: clean qemu
	gdb -ex 'target remote 127.0.0.1:1234' -ex 'b 16' $(BIN)

qemu: $(BIN)
	qemu-system-i386 -drive file=$(BIN),format=raw &> /dev/null &

$(BIN): $(OBJ)
	ld --oformat binary -Ttext 0x7c00 $< -o $@

%.att: %
	objdump -D -b binary -mi386 -Maddr16,data16 $< > $@

.PHONY: all clean debug qemu

