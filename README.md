# lol lib

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

Makes creating threads a little bit easier. Less clutter in your program if you use this function. **This still needs work.**

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

void* hello_world(void *threadid) {
    long tid;
    tid = (long)threadid;
    printf("Thread #%ld\n", tid);
}
```

## Client / Server

A simple client / server for communicating from a node and a server. **This still needs work.**

```c
// Server
lol_server(int portno);

// Client
lol_client(char *hostname, int portno, char *message);
```

### Example

```c
// Server.c
lol_server(8888);

// Client.c
lol_client("127.0.0.1", 8888, "Hi there, how are you?");
```

## Random numbers

Generate random numbers of various sizes.

```c
lol_init_rand(void); // must be called first
lol_rand_s(int min, int max); // create single random number
lol_rand_m(int min, int max, int num, int i_rand[num]); // random int array
lol_rand_entropy(int num, char e[num]); // create some entropy!
```

### Example

```c
/* Single random int */
lol_init_rand(void);
int i;
i = lol_rand_s(10, 50);

/* ***** */

/* array of random ints */
int num = 10;
int rns[num]; // random numbers
lol_rand_m(10, 50, num, rns);

/* ***** */

/* random string of entropy */
int e_num = 512;
char e[e_num];
lol_rand_entropy(e_num, e);
printf("%s\n", e);
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