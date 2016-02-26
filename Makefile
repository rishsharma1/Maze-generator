# Makefile  for workshop3 COMP20007
# Andrew Turpin
# March 2015

OBJ     = graph.o dfsMaze.o
SRC     = graph.c dfsMaze.c
EXE     = dfsMaze

CC    = g++
CDEFS = -Wall # -O2

maze:   $(OBJ) Makefile
	$(CC) $(CDEFS) -o $(EXE) $(OBJ)

clean:
	rm -f $(OBJ) $(EXE)

clobber: clean
	rm -f $(EXE)

usage: $(EXE)
	./$(EXE)

test: $(EXE)
	./$(EXE) 10
