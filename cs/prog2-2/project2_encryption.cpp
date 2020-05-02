/*	collin gros
	04/21/2020

	prog2-2 for CS478	*/

#include <stdio.h>
#include <stdlib.h>
#include <openssl/conf.h>

/*	maximum len of individual arguments	*/
#define MAX_ARG_SIZE 100


int parseArgs(int argc, char **argv, char *msg, char *pub, char *pri)
{
	if (argc != 4) {
		printf("ERROR: usage: [msg] [pubkeyfilename] [privkeyfilename]\n");
		return 1;
	}

	sprintf(msg, "%s", argv[1]);
	sprintf(pub, "%s", argv[2]);
	sprintf(pri, "%s", argv[3]);

	return 0;
}


int main(int argc, char **argv)
{
	char msg[MAX_ARG_SIZE];
	/*	third party public key - not my public key	*/
	char pubKeyFilename[MAX_ARG_SIZE];
	char priKeyFilename[MAX_ARG_SIZE];
	/*	the file we want to encrypt with AES - used in decrypt
		program	*/
	const char *ENC_FILE = "secrets.txt";
	/*	the decrypted file from the given msg	*/
	const char *MSG_DEC_FILE = "symmetric.txt";


	// parse our arguments, exit on failure
	if (parseArgs(argc, argv, msg, pubKeyFilename, priKeyFilename)) {
		printf("ERROR: parseArgs() failed!\n");
		exit(1);
	}


	printf("recieved arguments:\n\tmsg: %s\n\tpubKeyFilename: %s\n\t"
			"priKEyFilename: %s\n\n", msg, pubKeyFilename, priKeyFilename);


	printf("decrypting message with third party public key \"%s\", and "
			"storing it in symmetric.txt...", pubKeyFilename);
	/*	decrypt message with third party public key and store it
		in symmetric.txt	*/
	char buf[100 + MAX_ARG_SIZE * 3];
	sprintf(buf, "openssl rsautl -encrypt -raw -inkey "
			"%s -pubin -in %s -out %s", pubKeyFilename, msg, MSG_DEC_FILE);
	system(buf);
	printf("done\n\n");

	printf("using symmetric.txt symm key for AES encryption, "
			"and encrypting %s and outputing as encrypted.txt...",
			ENC_FILE);
	/*	use the decrypted message as a symm key to encrypt a text file
		with one of the symm key algos (AES or 3DES). write the code for
		this part OR use openssl command with system function.
		the text file MUST have my name and 800652097.
		explain which algo was used in project eval	*/
	sprintf(buf, "openssl aes-256-cbc -in %s "
			"-out encrypted.txt -pass file:%s",
			ENC_FILE, MSG_DEC_FILE);
	system(buf);
	printf("done\n\n");

	printf("signing encrypted.txt with %s and saving as "
			"encrypted-signed.txt...", priKeyFilename);
	/*	sign the file content with our private key, and store
		it in a file	*/
	sprintf(buf, "openssl dgst -sha256 -sign %s -out "
			"encrypted-signed.txt encrypted.txt",
			priKeyFilename);
	system(buf);
	printf("done\n\n");

	printf("encryption finished\n");


	return 0;
}



