# collin gros
# 04/14/2020
#
# simple makefile for compiling prog 2
cc=gcc
cf=-Wall -lcrypto -lssl


run.gitignoreme: extractPK.o
	$(cc) $(cf) extractPK.o


extractPK.o: extractPK.c
	$(cc) $(cf) -c extractPK.c


clean:
	rm -rf run.gitignoreme
	rm -rf *.o
