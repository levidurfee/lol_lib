#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include "libz/lol_inetz.h"
#include "libz/lol_threads.h"
#include "libz/lol_primes.h"

void* hello_world(void *threadid);

int main(int argc, char *argv[]) {
    int loops;
    if(argc == 1) {
        printf("%s loops\n", argv[0]);
        return -1;
    }
    init_locks();
    loops = atoi(argv[1]);
    //lol_server(9191);

    /* function, join_threads, loops, output */
    lol_threadz_s lts;
    lts.start_routine = hello_world;
    lts.join_threads = 1;
    lts.loops = loops;
    lts.output = 0;
    lol_threads(lts);

    kill_locks();
    //lol_client("levi.lol", 80);
    return 0;
}

void* hello_world(void *threadid) {
    long tid;
    char prime[512];
    lol_primes(prime, 56);
    tid = (long)threadid;
    printf("Hello World! It's me, thread #%ld! [%s]\n", tid, prime);
    pthread_exit(NULL);
}