#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include "lol_inetz.h"
#include "lol_threads.h"
#include "lol_primes.h"

void* hello_world(void *threadid);

int main(int argc, char *argv[]) {
    int loops;
    if(argc == 1) {
        printf("Err.\n");
        return -1;
    }
    loops = atoi(argv[1]);
    //lol_server(9191);
    /* function, join_threads, loops, output */
    lol_threads(hello_world, 1, loops, 0);
    
    return 0;
}

void* hello_world(void *threadid) {
    long tid;
    char prime[512];
    lol_primes(prime, 56);
    tid = (long)threadid;
    printf("Hello World! It's me, thread #%ld! [%s]\n", tid, prime);
    lol_client("localhost", 9191, prime);
    pthread_exit(NULL);
}