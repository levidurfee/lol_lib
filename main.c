#include <stdio.h>
#include "lol_primez.h"

int main() {
    size_t p_size = 256;
    //char entropy[ent];
    int i;
    char prime[p_size];
    srand(time(NULL)); // feed the machine
    /*for(i=0;i<10000000;i++) {
        if(l_rand_entropy(ent, entropy)) {
            printf("Entropy: %s\n", entropy);
        }
    }*/
    for(i=0;i<5;i++) {
        l_prime(p_size, prime, 0);
        printf("%s\n\n", prime);
    }
    return 1;
}
