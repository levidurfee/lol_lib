#include <stdio.h>
#include <time.h>
#include <omp.h>
#include <string.h>
#include "lol_types.h"
#include "lol_primez.h"

#define lol_clear() printf("\033[H\033[J")

int thread_test(lol_arg *arg, char *data);
void show_progress(size_t cur, size_t max, clock_t start, char *pp);
void do_nothing(int i);

int main(int argc, char *argv[]) {
    if(argc == 1) {
        printf("Err. Usage:\n%s num_of_primes bits\n", argv[0]);
        return -1;
    }
    
    size_t max = atoi(argv[1]);             // number of primes
    size_t bit = atoi(argv[2]);             // number of bits
    
    clock_t start;                          // start time var
    time(&start);                           // start time
    
    /* thread args */
    char *pp = malloc(sizeof(char*) * bit); // allocate space for char ptr
    
    lol_arg *la = lol_arg_new(max, 1, 1, bit);
    
    int nthreads, tid;                      // declare omp args
    nthreads = tid = 0;                     // initialize omp args
    
    #pragma omp parallel for private(nthreads, tid)
    for(int i=0;i<la->max;i++) {
        thread_test(la, pp);
        show_progress(la->cur, la->max, start, pp);
    }
    free(pp);
    lol_arg_free(la);                       // free the malloc
    
    do_nothing(nthreads);                   // do nothing with them
    do_nothing(tid);                        // so there isn't a warning
    
    return 1;
}

void show_progress(size_t cur, size_t max, clock_t start, char *pp) {
    clock_t stop;
    time(&stop);
    double time_taken = (double)difftime(stop, start) / 60 / 60;
    double per_hour = (double)cur / time_taken;
    double total_time = (double)max / per_hour;
    double time_remaining = total_time - time_taken;
    double percent_done = ((double)cur * 100) / max;
    lol_clear();
    printf("Time elapsed:       %f\n", time_taken);
    printf("Per hour:           %f\n", per_hour);
    printf("Total time needed:  %f\n", total_time);
    printf("Time remaining:     %f\n", time_remaining);
    printf("Percent done:       %f\n", percent_done);
    printf("                    %zu/%zu\n", cur, max);
    printf("Data:               %s\n", pp);
}

int thread_test(lol_arg *arg, char *data) {
    // libcrypto has lots of memory leaks
    // make test = 1 if debugging. otherwise
    // you'll see a lot of extra info
    int test = 0;
    if(test == 0) {
        int tid;                        // int for thread id
        tid = omp_get_thread_num();     // get thread id from omp
        size_t p_size = arg->bit;       // prime bits
        char prime[p_size];             // char array to hold prime
        srand(time(NULL));              // feed the machine
        l_prime(p_size, prime, 0);      // bits, prime ptr, safe prime
        
        /* copy the tid & prime to the pointer */
        sprintf(data, "tid: %i prime: %s", tid, prime);
        arg->cur++;                     // increment the pointer
        
        /* Write the prime to the file */
        FILE *fp;
        fp = fopen("output.pri", "a");
        fprintf(fp, "%s\n", prime);
        fclose(fp);
    } else {
        printf("Debugging\n");
    }
    return 1;
}

void do_nothing(int i) {
    // do nothing
}
