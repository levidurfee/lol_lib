#include <stdio.h>
#include "lol_primez.h"
#include "lol_threadz.h"

void *thread_test(void *arg);

int main() {
    /* thread args */
    lol_arg *la = lol_arg_new(10, 1, "Hello", 5);
    
    /* thread stuff */
    lol_threadz *lt = lol_threadz_new( 0, 2, 1, thread_test, la);
    
    int i;                      // int for looping
    for(i=0;i<4;i++) {
        lol_threadz_create(lt); // create the threads and wait
    }
    lol_arg_free(la);           // free the malloc
    lol_threadz_free(lt);       // free the malloc
    
    pthread_exit(NULL);         // end the threads
    
    return 1;
}

void *thread_test(void *arg) {
    // try and use new lol_arg_copy function
    lol_arg *la = malloc(sizeof(lol_arg));
    if(la == NULL) {
        printf("Error: couldn't allocate lol_arg memory\n");
    }
    memcpy(la, arg, sizeof(lol_arg));
    
    // libcrypto has lots of memory leaks
    // make test = 1 if debugging. otherwise
    // you'll see a lot of extra info
    int test = 1;
    if(test == 0) {
        size_t p_size = 1024;
        char prime[p_size];
        srand(time(NULL)); // feed the machine
        printf("%i thread_test: %s %i\n", la->tid, la->data, la->cur);
        l_prime(p_size, prime, 0);
        printf("\t%s\n\n", prime);
    } else {
        printf("Debugging\n");
    }
    free(la);
    pthread_exit(NULL);
}
