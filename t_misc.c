#include <stdio.h>
#include <stdlib.h>
#include "libz/lol_misc.h"

int main(int argc, char *argv[]) {
    if(argc == 1) {
        printf("Err.\n");
        return -1;
    }
    int rn; // Random Number
    int max;
    
    lol_init_rand(); // init rand w/ srand
    
    max = atoi(argv[1]);
    rn = lol_s_rand(max); // get single rand number
    printf("%d\n", rn);
    
    int i;
    int num = 10; // number of rans
    int rns[num]; // random numbers
    lol_m_rand(max, num, rns);
    for(i=0;i<num;i++) {
        printf("%i\n", rns[i]);
    }
    
    return 0;
}