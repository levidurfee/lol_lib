#include <stdio.h>
#include <stdlib.h>
#include "libz/lol_misc.h"

int main(int argc, char *argv[]) {
    if(argc == 1) {
        printf("Err.\n");
        return -1;
    }
    /* random single number */
    int rn; // Random Number
    int max;
    
    lol_init_rand(); // init rand w/ srand
    
    max = atoi(argv[1]);
    rn = lol_rand_s(0, max); // get single rand number
    printf("%d\n", rn);
    /* end random single number */
    
    /* create array of random numbers */
    int i;
    int num = atoi(argv[2]); // number of rans
    int rns[num]; // random numbers
    lol_rand_m(0, max, num, rns);
    for(i=0;i<num;i++) {
        //printf("%i\n", rns[i]);
    }
    /* end array of random numbers */
    
    /* create entropy */
    int e_num = 256;
    char e[e_num];
    lol_rand_entropy(e_num, e);
    printf("%s\n", e);
    
    /* end entropy */
    
    return 0;
}