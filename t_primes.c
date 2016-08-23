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
        printf("Err. Usage:\n%s num_of_primes", argv[0]);
        return -1;
    }
    loops = atoi(argv[1]);
    init_locks();
    /* function, join_threads, loops, output */
    lol_threadz_s lts;
    lts.start_routine = hello_world;
    lts.join_threads = 1;
    lts.loops = loops;
    lts.output = 1;
    lol_threads(lts);
    kill_locks();
    return 0;
}

void* hello_world(void *threadid) {
    int bits;
    long tid;
    char prime[8192];
    char filename[20];
    FILE *fp;
    bits = 4096;
    lol_primes(prime, bits);
    tid = (long)threadid;
    
    printf(LOL_CYAN "Hello World! It's me, thread #%02ld!" LOL_GREEN " ["\
                        LOL_RESET "%.50s..." LOL_GREEN "]" LOL_RESET "\n", 
                        tid, prime);
    sprintf(filename, "%i-bits.pri", bits);
    fp = fopen(filename, "a");
    
    fwrite(prime, 1, strlen(prime), fp);
    fwrite("\n", 1, strlen("\n"), fp);
    fclose(fp);
    pthread_exit(NULL);
}
