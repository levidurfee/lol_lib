#include <stdio.h>
#include "lol_primez.h"

int main() {
    int ent = 1024, i;
    char entropy[ent];
    srand(time(NULL)); // feed the machine
    for(i=0;i<10000000;i++) {
        if(l_rand_entropy(ent, entropy)) {
            printf("Entropy: %s\n", entropy);
        }
    }
    return 1;
}
