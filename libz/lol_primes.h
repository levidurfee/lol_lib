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

static pthread_mutex_t *lockarray;

static void lock_callback(int mode, int type, char *file, int line);
static unsigned long thread_id(void);
static void init_locks(void);
static void kill_locks(void);
void lol_primes(char *r_string, int bits);

void lol_primes(char *r_string, int bits) {
    BIGNUM *r;
    int e_num = 512;
    char *e = (char *)malloc(e_num * sizeof(char));
    if(e == NULL) {
        printf("Malloc messed up\n");
    }
    printf("e lives at %p.\n", (void*)&e);
    lol_init_rand();
    lol_rand_entropy(e_num, e);
    r = BN_new();
    RAND_seed(e, sizeof e);
    BN_generate_prime_ex(r, bits, 0, NULL, NULL, NULL);
    sprintf(r_string, "%s", BN_bn2dec(r));
    //printf("Free S: %s.\n", e);
    //free(e);
    //printf("S Freed\n");
    BN_clear_free(r);
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
