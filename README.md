# lol lib

## lol misc

## Prime numbers

Create a prime number using the OpenSSL library. It also uses the `lol_rand_entropy` function.


```c
lol_primes(char *r_string, int bits)
```

### Example

```c
char prime[512];
lol_primes(prime, 2048);
```

## Threads

Makes creating threads a little bit easier. Less clutter in your program if you use this function.

```c
lol_threads(
        void *(*start_routine) (void *), 
        int join_threads,
        int loops,
        int output)
```

### Example

```c
void* hello_world(void *threadid);

void main(void) {
    lol_threads(hello_world, 1, 0, 0);
}

void hell_world(void *threadid) {
    long tid;
    tid = (long)threadid;
    printf("Thread #%ld\n", tid);
}
```

## Simple int swap

Change int variable `a` to int variable `b` and int variable `b` to int variable `a`.

```c
lol_int_swap(int *a, int *b)
```

### Example

```c
int isa = 20;
int isb = 30;
lol_int_swap(isa, isb);
```