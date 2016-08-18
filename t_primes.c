#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include "libz/lol_threads.h"
#include "libz/lol_primes.h"
#include "libz/lol_crypt.h"
#define  MAX_LEN  80

void* hello_world(void *threadid);

int main(int argc, char *argv[]) {
    int loops;
    if(argc == 1) {
        printf("Err.\n");
        return -1;
    }
    loops = atoi(argv[1]);

    /* function, join_threads, loops, output */
    lol_threadz_s lts;
    lts.start_routine = hello_world;
    lts.join_threads = 1;
    lts.loops = loops;
    lts.output = 0;
    lol_threads(lts);
    
    return 0;
}

void* hello_world(void *threadid) {
    long tid;
    char prime[4096];
    FILE *fp;
    
    lol_primes(prime, 2048);
    tid = (long)threadid;
    printf("Hello World! It's me, thread #%ld! [%s]\n", tid, prime);
    
    fp = fopen("output.txt", "a");
    
    fwrite(prime, 1, strlen(prime), fp);
    fwrite("\n", 1, strlen("\n"), fp);
    fclose(fp);
    pthread_exit(NULL);
}