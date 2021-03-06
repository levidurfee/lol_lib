#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/md5.h>
#include <openssl/sha.h>
#include "lol_hash.h"

char *lol_md5(const char *str) {
    int n;                          // declare before loop
    MD5_CTX c;                      // declare md5 context
    unsigned char digest[16];       // digest
    char *out = (char*)malloc(33);  // allocate 32+1

    MD5_Init(&c);                   // initialize md5 context

    MD5_Update(&c, str, strlen(str));

    MD5_Final(digest, &c);

    for(n=0;n<16;++n) {
        snprintf(&(out[n*2]), 32, "%02x", (unsigned int)digest[n]);
    }

    return out;
}

char *lol_sha(const char *str) {
    int n;                                      // declare before loop
    SHA512_CTX c;                               // declare sha512
    unsigned char digest[SHA512_DIGEST_LENGTH]; // digest
    char *out = (char*)malloc(129);             // allocatte 128+1
    
    SHA512_Init(&c);                            // initialize sha512 ctx
    
    SHA512_Update(&c, str, strlen(str));
    SHA512_Final(digest, &c);

    for(n=0;n<SHA512_DIGEST_LENGTH;n++) {
        snprintf(&(out[n*2]), 128, "%02x", (unsigned int)digest[n]);
    }

    return out;
}

int lol_b64(const char *str) {
    BIO *bio, *b64;

    b64 = BIO_new(BIO_f_base64());          // new Basic I/O abstraction
    bio = BIO_new_fp(stdout, BIO_NOCLOSE);  // where to output - stdout
    BIO_push(b64, bio);                     // append
    BIO_write(b64, str, strlen(str));       // write it
    BIO_flush(b64);                         // flush

    BIO_free_all(b64);                      // free the bio
    return 1;
}
