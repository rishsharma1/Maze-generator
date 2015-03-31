# Makefile 
# Andrew Turpin
# March 2013

OBJ     = main.o hoare.o radixSort.o partition.o
CC      = gcc
EXE     = findKth

findKth:   $(OBJ) Makefile
	$(CC) -o $(EXE) $(OBJ)

clean:
	rm -f $(OBJ) $(EXE)

clobber: clean
	rm -f $(EXE)

usage: $(EXE)
	./$(EXE) 

random: 
	od -t u /dev/random | awk '{print $$2/4}' | head -10000 > t1

main.o: partition.h radixSort.h hoare.h Makefile
partition.o: partition.h 
radixSort.o: radixSort.h 

zip: 
	zip work2.zip Makefile hoare.c hoare.h main.c partition.c\
                  partition.h radixSort.c radixSort.h work2.pdf

#########################
# Tricky define of a test case
# so make test will work...
# Will it work on lab machines?
#########################
define TEST
1
2
3
4
5
6
7
endef
export TEST

test: $(EXE)
	echo "$$TEST" | ./$(EXE) h
	echo "$$TEST" | ./$(EXE) r
	 ./$(EXE) h < t1
	 ./$(EXE) r < t1
