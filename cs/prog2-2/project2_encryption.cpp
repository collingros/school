/*	collin gros
	04/21/2020

	prog2-2 for CS478	*/

#include <stdio.h>
#include <stdlib.h>
#include <openssl/bio.h>

#define MAX_ARG_SIZE 100


int main(int argc, char **argv)
{
	char pkFilename[MAX_ARG_SIZE];
	sprintf(pkFilename, "%s", argv[2]);

	BIO *pkbio = BIO_new_file(pkFilename, "r");


	exit(1);
}

/* as command line args:	*/
	/*	take the encrypted message	*/
	/*	take third party public key	*/
	/*	take our private key	*/

/*	use the third party public key to decrypt the encrypted message	*/

/*	store the message in a text file, symmetric.txt (this is our
	symmetric key	*/

/*	use the decrypted message as a symm key to encrypt a text file
	with one of the symm key algos (AES or 3DES). write the code for
	this part OR use openssl command with system function. the text file
	MUST have my name and 800652097. explain which algo was used in project
	eval	*/

/*	sign the file content with our private key, and store it in a file	*/

