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
    int i;
    for(i=0;i<100;i++) {
        lol_threadz_create(lt);
    }
    pthread_exit(NULL);
    
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
    if(la == NULL) {
        printf("Error: couldn't allocate lol_arg memory\n");
    }
    memcpy(la, arg, sizeof(lol_arg));
    printf("thread_test: %s\n", la->data);
    free(la);
    pthread_exit(NULL);
}
