# collin gros
# 04/21/2020
#
# simple makefile for compiling prog2-2

cc=g++
cf=-Wall -lcrypto -lssl


run.gitignoreme: project2_encryption.o
	$(cc) project2_encryption.o $(cf) -o run.gitignoreme


project2_encryption.o: project2_encryption.cpp
	$(cc) -c project2_encryption.cpp $(cf)


clean:
	rm -rf run.gitignoreme
	rm -rf *.o
