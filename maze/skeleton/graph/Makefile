# Makefile  for workshop3 COMP20007
# Andrew Turpin
# March 2015

OBJ     = graph.o input.o
SRC     = graph.c input.c
EXE     = input1

CC    = g++
CDEFS = -Wall # -O2

input:   $(OBJ) Makefile
	$(CC) $(CDEFS) -o $(EXE) $(OBJ)

clean:
	rm -f $(OBJ) $(EXE)

clobber: clean
	rm -f $(EXE)

usage: $(EXE)
	./$(EXE)

test: $(EXE)
	./$(EXE) 10
