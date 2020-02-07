# collin gros
# 02/07/2020
#
# compiles symtable.c along with its header file
#

# create our executable
all: symtable.o
	gcc -o run symtable.o

# compile symtable.c
symtable.o: symtable.c symtable.h
	gcc -c symtable.c

# get rid of generated crap
clean:
	rm run
