/*	collin gros
	04/14/2020

	prog 2 assignment; extracts a public key and priv key from a given
	certificate	*/

#include <openssl/bio.h>
#include <openssl/pem.h>
#include <openssl/x509.h>
#include <stdio.h>

#define CERT_FILENAME	"cert.pem"


int main()
{
	/*	for reading/writing the file	*/
	BIO *certb = BIO_new(BIO_s_file());
	BIO *outb = BIO_new_fp(stdout, BIO_NOCLOSE);

	/*	attempt reading the cert, returns 0 for failure	*/
	if (!BIO_read_filename(certb, CERT_FILENAME)) {
		printf("ERROR: couldn't find cert file!\n");
		return 1;
	}

	/*	get the X509 of the certificate	*/
	X509 *certx = PEM_read_bio_X509(certb, NULL, 0, NULL);
	if (certx == NULL) {
		printf("ERROR: failed to get certx!\n");
		return 1;
	}

	/*	get the public key from the X509 data	*/
	EVP_PKEY *pubkey = X509_get_pubkey(certx);
	if (pubkey == NULL) {
		printf("ERROR: failed to get pubkey!\n");
		return 1;
	}

	/*	print the public key to stdout	*/
	if (!PEM_write_bio_PUBKEY(outb, pubkey)) {
		printf("ERROR: failed to print pubkey!\n");
		return 1;
	}


	/*	cleanup	*/
	EVP_PKEY_free(pubkey);
	X509_free(certx);
	BIO_free_all(certb);
	BIO_free_all(outb);

	return 0;
}
