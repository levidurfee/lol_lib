#ifndef LOL_PRIMEZ_H
#define LOL_PRIMEZ_H
int l_rand_int(int min, int max);
int l_rand_entropy(size_t n_chars, char entropy[n_chars]);
int l_prime(size_t bits, char *prime, int safe);
#endif
