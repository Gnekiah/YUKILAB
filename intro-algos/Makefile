CC = gcc
OBJECT = algos.o
HEAD = algos.h

insertion-sort: $(OBJECT)
	gcc -o insertion-sort.c $(OBJECT)
#insertion-sort.o: insertion-sort.c $(HEAD)
#	gcc -c insertion-sort.c
algos.o: algos.c algos.h
	gcc -c algos.c

.PHONY: clean
clean:
	rm $(OBJECT)

