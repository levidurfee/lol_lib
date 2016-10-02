#include <stdio.h>
#include <time.h>
#include <omp.h>
#include <string.h>
#include "lol_types.h"
#include "lol_primez.h"

#define lol_clear() printf("\033[H\033[J")

int thread_test(lol_arg *arg);
void show_progress(size_t cur, size_t max, clock_t start, char *data);

int main(int argc, char *argv[]) {
    if(argc == 1) {
        printf("Err. Usage:\n%s num_of_primes bits\n", argv[0]);
        return -1;
    }
    
    size_t max = atoi(argv[1]);
    size_t bit = atoi(argv[2]);
    
    clock_t start;
    time(&start);
    /* thread args */
    lol_arg *la = lol_arg_new(max, 1, "Hello", 5, bit);
    int nthreads, tid;
    #pragma omp parallel for private(nthreads, tid)
    for(int i=0;i<la->max;i++) {
        thread_test(la);
        show_progress(la->cur, la->max, start, la->data);
    }
    lol_arg_free(la);           // free the malloc
    
    return 1;
}

/* @todo the time is skewed / wrong */
void show_progress(size_t cur, size_t max, clock_t start, char *data) {
    clock_t t;
    time(&t);
    double time_taken = (double)difftime(t, start) / 60 / 60;
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
    printf("Data:               %i\n", data);
}

int thread_test(lol_arg *arg) {
    // libcrypto has lots of memory leaks
    // make test = 1 if debugging. otherwise
    // you'll see a lot of extra info
    int test = 0;
    if(test == 0) {
        int tid;
        tid = omp_get_thread_num();
        size_t p_size = arg->bit;
        char prime[p_size];
        srand(time(NULL)); // feed the machine
        l_prime(p_size, prime, 0);
        arg->data = prime;
        // get time started and how many have been generated to get
        // the threads per hour and estimated time left. maybe make
        // a progress bar.
        printf("thread: %i\nprime: %s\n\n", tid, prime);
        arg->cur++;
        
        FILE *fp;
        fp = fopen("output.pri", "a");
        fprintf(fp, "%s\n", prime);
        fclose(fp);
    } else {
        printf("Debugging\n");
    }
    return 1;
}
