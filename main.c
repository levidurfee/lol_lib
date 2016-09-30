#include <stdio.h>
#include "lol_primez.h"

int main() {
    int i;
    char *entropy = NULL;
    srand(time(NULL)); // feed the machine
    i = l_rand_int(0, 1024);
    printf("%i\n", i);
    l_rand_entropy(10, entropy);
    printf("\n");
    free(entropy);
    return 1;
}
