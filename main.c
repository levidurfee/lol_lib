#include <stdio.h>
#include "lol_primez.h"
#include "lol_threadz.h"

void *thread_test(void *arg);

int main() {
    /* thread stuff */
    lol_threadz lt;
    lt.debug = 1;
    lt.num_threads = 2;
    lt.join_threads = 1;
    lt.lfptr = &thread_test;
    
    lol_arg la;
    la.max = 10;
    la.cur = 1;
    la.data = "Hello";
    
    lt.la = &la;
    
    lol_threadz_create(lt);
    
    /* prime stuff */
    /*
    size_t p_size = 256;
    //char entropy[ent];
    int i;
    char prime[p_size];
    srand(time(NULL)); // feed the machine
    for(i=0;i<2;i++) {
        if(l_rand_entropy(ent, entropy)) {
            printf("Entropy: %s\n", entropy);
        }
    }
    for(i=0;i<5;i++) {
        l_prime(p_size, prime, 0);
        printf("%s\n\n", prime);
    }
    */
    return 1;
}

void *thread_test(void *arg) {
    lol_arg *la = malloc(sizeof(lol_arg));
    la = arg;
    printf("Thread test function in main\n");
    printf("%s\n", la->data);
    pthread_exit(NULL);
}
