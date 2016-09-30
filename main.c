#include <stdio.h>
#include "lol_primez.h"

int main() {
    int ent = 10;
    char entropy[ent];
    srand(time(NULL)); // feed the machine
    if(l_rand_entropy(ent, entropy)) {
        printf("Entropy: %s\n", entropy);
    }
    return 1;
}
