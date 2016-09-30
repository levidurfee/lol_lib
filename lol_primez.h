#include <string.h>
#include <stdlib.h>
#include <openssl/bn.h>
#include <time.h>

#ifndef _LOL_PRIMEZ
#define _LOL_PRIMEZ
int l_rand_int(int min, int max);
int l_rand_entropy(size_t n_chars, char entropy[n_chars]);
int l_prime(int bits, char *prime);

int l_rand_int(int min, int max) {
    return rand() % (max + 1 - min) + min;
}

int l_rand_entropy(size_t n_chars, char entropy[n_chars]) {
    int i, c;
    // add + 1 to account for \0
    //char *p_buf = malloc((sizeof(char) * n_chars) + 1);
    char *p_buf = calloc(n_chars, sizeof(char) + 1);
    if(p_buf == 0) {
    	printf("Error: Out of memory\n");
    	return -1;
    }
    for(i=0;i<n_chars;i++) {
        c = l_rand_int(33, 125); // ascii chars
        //printf("%c", c);
        //snprintf(p_buf, 1, "%c", c);
        *p_buf = (char)c;
        p_buf++;
        //printf("%p\n", p_buf);
    }
    strcpy(entropy, p_buf - i);
    free(p_buf - i);
    return 1;
}

#endif
