#include <string.h>
#include <stdlib.h>

#ifndef _LOL_PRIMEZ
#define _LOL_PRIMEZ
int l_rand_int(int min, int max);
int l_rand_entropy(size_t n_chars, char entropy[n_chars]);
int l_prime(size_t bits, char *prime, int safe);
#endif
