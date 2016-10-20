#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/md5.h>
#include <openssl/sha.h>
#include "lol_hash.h"

char *lol_md5(const char *str, int length) {
    int n;
    MD5_CTX c;
    unsigned char digest[16];
    char *out = (char*)malloc(33);

    MD5_Init(&c);

    while(length > 0) {
        if (length > 512) {
            MD5_Update(&c, str, 512);
        } else {
            MD5_Update(&c, str, length);
        }
        length -= 512;
        str += 512;
    }

    MD5_Final(digest, &c);

    for(n=0;n<16;++n) {
        snprintf(&(out[n*2]), 16*2, "%02x", (unsigned int)digest[n]);
    }

    return out;
}

char *lol_sha(const char *str, int length) {
    int n;
    SHA512_CTX c;
    unsigned char digest[SHA512_DIGEST_LENGTH];
    char *out = (char*)malloc(129);
    
    SHA512_Init(&c);
    
    SHA512_Update(&c, str, strlen(str));
    SHA512_Final(digest, &c);

    for(n=0;n<SHA512_DIGEST_LENGTH;n++) {
        snprintf(&(out[n*2]), 128, "%02x", (unsigned int)digest[n]);
    }

    return out;
}
