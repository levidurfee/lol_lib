#include <stdio.h>
#include "lol_primez.h"

int main() {
    int ent = 1024;
    //char entropy[ent];
    int i;
    char prime[ent];
    srand(time(NULL)); // feed the machine
    /*for(i=0;i<10000000;i++) {
        if(l_rand_entropy(ent, entropy)) {
            printf("Entropy: %s\n", entropy);
        }
    }*/
    for(i=0;i<10000000;i++) {
        l_prime(1024, prime, 0);
        printf("%s\n\n", prime);
    }
    return 1;
}
