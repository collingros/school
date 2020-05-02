# collin gros
# 04/21/2020
#
# simple makefile for compiling prog2-2

cc=g++
cf=-Wall -lcrypto -lssl

all: enc.gitignoreme dec.gitignoreme

enc.gitignoreme: project2_encryption.o
	$(cc) project2_encryption.o $(cf) -o enc.gitignoreme

dec.gitignoreme: project2_decryption.o
	$(cc) project2_decryption.o $(cf) -o dec.gitignoreme


project2_encryption.o: project2_encryption.cpp
	$(cc) -c project2_encryption.cpp $(cf)

project2_decryption.o: project2_decryption.cpp
	$(cc) -c project2_decryption.cpp $(cf)


clean:
	rm -rf enc.gitignoreme dec.gitignoreme
	rm -rf symmetric.txt encrypted.txt encrypted-signed.txt
	rm -rf plaintext.txt
	rm -rf *.o
