#include <string.h>
#include <stdlib.h>
#include <openssl/bn.h>
#include <openssl/rand.h>
#include <time.h>

#ifndef _LOL_PRIMEZ
#define _LOL_PRIMEZ
int l_rand_int(int min, int max);
int l_rand_entropy(size_t n_chars, char entropy[n_chars]);
int l_prime(size_t bits, char *prime, int safe);

int l_rand_int(int min, int max) {
    return rand() % (max + 1 - min) + min;
}

int l_rand_entropy(size_t n_chars, char entropy[n_chars]) {
    int i, c;

    // add + 1 to account for \0
    char *p_buf = calloc(n_chars, sizeof(char) + 1);

    // check and see if calloc was successful
    if(p_buf == 0) {
        printf("Error: Out of memory\n");
        return -1;
    }

    for(i=0;i<n_chars;i++) {
        c = l_rand_int(33, 125);    // ascii chars
        *p_buf = (char)c;           // cast the int to char
        p_buf++;                    // increment the pointer
    }

    // copy the buffer to the char array
    strcpy(entropy, p_buf - i);

    // free the memory. - i gets us back to the original location of memory
    free(p_buf - i);

    // great success!
    return 1;
}

int l_prime(size_t bits, char *prime, int safe) {
    BIGNUM *p;
    char seed[bits];

    // get some entropy to feed the machine
    l_rand_entropy(bits, seed);
    RAND_seed(seed, sizeof seed);

    // initialize the new big number
    p = BN_new();
    
    // generate the prime
    if(BN_generate_prime_ex(p, bits, 0, NULL, NULL, NULL) != 1) {
        printf("Error generating prime\n");
        return -1;
    }

    // copy the big number to a char pointer
    sprintf(prime, "%s", BN_bn2dec(p));

    // free the memory used by the big number
    BN_free(p);

    // YAY
    return 1;
}

#endif
