# Macros
CC = gcc217

# Dependency rules for non-file targets
all: testsymtable
clobber: clean
	rm -f *~ \#*\#
clean:
	rm -f testsymtable *.o
  
# Dependency rules for file targets
testsymtable: testsymtable.o symtablehash.o
	$(CC) testsymtable.o symtablehash.o –o testsymtable
testsymtable.o: testsymtable.c symtable.h
	$(CC) -c testsymtable.c
symtablehash.o: symtablehash.c symtable.h
	$(CC) -c symtablehash.c