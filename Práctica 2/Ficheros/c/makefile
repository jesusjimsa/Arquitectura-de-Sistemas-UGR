ATT = $(SRC:.c=.att)
EXE = $(basename $(SRC))
SRC = $(wildcard *.c)

CFLAGS = -ffreestanding -g -nostdlib -m32 -Og -static -Tlinker.ld -Wall -Werror -Wl,-melf_i386

default: $(EXE) $(ATT) qemu

clean:
	$(RM) $(ATT) $(EXE) core.* *~

qemu: $(EXE)
	qemu-system-i386 -drive file=$<,format=raw &> /dev/null &

%.att: %
	objdump -b binary -m i8086 -D $< > $@

.PHONY: clean default qemu

