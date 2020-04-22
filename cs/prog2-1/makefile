# collin gros
# 04/14/2020
#
# simple makefile for compiling prog 2
cc=gcc
cf=-Wall -lcrypto -lssl


run.gitignoreme: extractPK.o
	$(cc) extractPK.o $(cf) -o run.gitignoreme


extractPK.o: extractPK.c
	$(cc) -c extractPK.c $(cf)


clean:
	rm -rf run.gitignoreme
	rm -rf *.o
