#include <strings.h>
#include <openssl/bn.h>
#include <time.h>

#ifndef _LOL_PRIMEZ
#define _LOL_PRIMEZ
int l_rand_int(int min, int max);
int l_rand_entropy(int n_chars, char *entropy);
int l_prime(int bits, char *prime);

int l_rand_int(int min, int max) {
    return rand() % (max + 1 - min) + min;
}

int l_rand_entropy(int n_chars, char *entropy) {
    int i, c;    
    for(i=0;i<n_chars;i++) {
        c = l_rand_int(33, 125); // ascii chars
        printf("%c", c);
    }
    return 1;
}

#endif
