collin gros
05/01/2020

i use AES-256-CBC for encryption/decryption

if symmetric.txt is missing, or the encrypted file is missing, just
run enc.gitignoreme to generate them. they will get deleted again
after a 'make clean'.

some of the default files in this directory:
	secrets.txt (the text file we want to encrypt and sign)
	keys/mypubkey.pem (my public key)
	keys/privkey.pem (my private key)
	keys/pubkey.pem (the third party public key)
	keys/symm_key.bin (the encrypted message)

to compile (both programs):
	make

to run project2_encryption.cpp:
	./enc.gitignoreme keys/symm_key.bin keys/pubkey.pem keys/privkey.pem
this will generate several files:
	symmetric.txt (the decrypted key used for AES for encrypting the
					plaintext)
	encrypted.txt (the encrypted plaintext)
	encrypted-signed.txt (the signed version of the encrypted plaintext)

to run project2_decryption.cpp:
	./dec.gitignoreme encrypted-signed.txt keys/mypubkey.pem symmetric.txt 
this will generate a single file:
	plaintext.txt (the result from decrypting encrypted.txt with AES and
					using symmetric.txt as the key)

to clean all generated files:
	make clean


