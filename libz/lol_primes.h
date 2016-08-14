/*
 *  _            _   _       _ 
 * | | _____   _(_) | | ___ | |
 * | |/ _ \ \ / / | | |/ _ \| |
 * | |  __/\ V /| |_| | (_) | |
 * |_|\___| \_/ |_(_)_|\___/|_|
 *
 * prime helper library
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/bn.h>
#include <openssl/rand.h>
#include <openssl/crypto.h>
#include "lol_misc.h"

void lol_primes(char *r_string, int bits) {
    BIGNUM *r;
    
    int e_num = 512;
    char e[e_num];
    lol_init_rand();
    lol_rand_entropy(e_num, e);
    
    static const char *rnd_seed = NULL;
    rnd_seed = e;
    
    r = BN_new();
    RAND_seed(rnd_seed, sizeof rnd_seed);
    BN_generate_prime_ex(r, bits, 0, NULL, NULL, NULL);
    strcpy(r_string, BN_bn2dec(r));

    BN_free(r);
}