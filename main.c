#include <stdio.h>
#include "lol_primez.h"

int main() {
    int ent = 10;
    char entropy[ent];
    srand(time(NULL)); // feed the machine
    l_rand_entropy(ent, entropy);
    printf("Entropy: %s", entropy);
    printf("\n");
    return 1;
}
