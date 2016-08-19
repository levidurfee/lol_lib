#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include "libz/lol_threads.h"
#include "libz/lol_primes.h"
#include "libz/lol_crypt.h"
#include "libz/lol_colors.h"
#define  MAX_LEN  80

void* hello_world(void *threadid);

int main(int argc, char *argv[]) {
    int loops;
    if(argc == 1) {
        printf("Err.\n");
        return -1;
    }
    loops = atoi(argv[1]);
    init_locks();
    /* function, join_threads, loops, output */
    lol_threadz_s lts;
    lts.start_routine = hello_world;
    lts.join_threads = 1;
    lts.loops = loops;
    lts.output = 0;
    lol_threads(lts);
    kill_locks();
    return 0;
}

void* hello_world(void *threadid) {
    long tid;
    char prime[1024];
    FILE *fp;
    lol_primes(prime, 2048);
    tid = (long)threadid;
    
    printf(LOL_CYAN "Hello World! It's me, thread #%ld!" LOL_GREEN " ["\
                        LOL_CYAN "%s" LOL_GREEN "]" LOL_RESET "\n", 
                        tid, prime);
    
    fp = fopen("output.txt", "a");
    
    fwrite(prime, 1, strlen(prime), fp);
    fwrite("\n", 1, strlen("\n"), fp);
    fclose(fp);
    pthread_exit(NULL);
}