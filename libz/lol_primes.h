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

static void lock_callback(int mode, int type, char *file, int line);
static unsigned long thread_id(void);
static void init_locks(void);
static void kill_locks(void);
void lol_primes(char *r_string, int bits);

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

static void lock_callback(int mode, int type, char *file, int line) {
    (void)file;
    (void)line;
    if (mode & CRYPTO_LOCK) {
        pthread_mutex_lock(&(lockarray[type]));
    }
    else {
        pthread_mutex_unlock(&(lockarray[type]));
    }
}

static unsigned long thread_id(void) {
    unsigned long ret;

    ret=(unsigned long)pthread_self();
    return(ret);
}

static void init_locks(void) {
    int i;

    lockarray=(pthread_mutex_t *)OPENSSL_malloc(CRYPTO_num_locks() *
                                        sizeof(pthread_mutex_t));
    for (i=0; i<CRYPTO_num_locks(); i++) {
        pthread_mutex_init(&(lockarray[i]),NULL);
    }

    CRYPTO_set_id_callback((unsigned long (*)())thread_id);
    CRYPTO_set_locking_callback((void (*)(int, int, const char*, int))lock_callback);
}

static void kill_locks(void) {
    int i;

    CRYPTO_set_locking_callback(NULL);
    for (i=0; i<CRYPTO_num_locks(); i++) {
        pthread_mutex_destroy(&(lockarray[i]));
    }

    OPENSSL_free(lockarray);
}