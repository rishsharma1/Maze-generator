# Makefile 
# Andrew Turpin
# March 2013

OBJ     = dfsMazeSkeleton.o
SRC     = dfsMazeSkeleton.c
EXE     = dfsMaze

CC    = gcc 
CDEFS = -Wall # -O2

ass1sort:   $(OBJ) Makefile
	$(CC) $(CDEFS) -o $(EXE) $(OBJ)

clean:
	rm -f $(OBJ) $(EXE)

clobber: clean
	rm -f $(EXE)

usage: $(EXE)
	./$(EXE)

test: $(EXE)
	./$(EXE) 10
