SRC = $(wildcard *.c *.cc)
EXE = $(basename $(SRC))

CFLAGS = -march=native -O3 -pthread -Wall
CXXFLAGS = $(CFLAGS) -std=c++11
LDFLAGS = -lpthread -lrt

default: $(EXE)

clean:
	-rm -fv $(EXE) *~ core.*

.PHONY: clean default
