#include <stdio.h>
#include <stdlib.h>
#include "libz/lol_misc.h"

int main(int argc, char *argv[]) {
    if(argc == 1) {
        printf("%s max\n", argv[0]);
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
    int e_num = 512;
    char e[e_num];
    lol_rand_entropy(e_num, e);
    printf("%s\n", e);
    /* end entropy */
    
    /* begin int swap*/
    int isa, isb; // int swap a / b
    isa = 20;
    isb = 40;
    printf("before\nisa: %i isb: %i\n", isa, isb);
    lol_int_swap(&isa, &isb);
    printf("after\nisa: %i isb: %i\n", isa, isb);
    /* end int_swap */
    
    return 0;
}