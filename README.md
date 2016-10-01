# lol lib

> old code had a lot of memory leaks, so i am redoing it from scratch, testing it as i go

i've been reading books on C that will hopefully help me develop a more solid library.

## examples

```c
/* prime stuff */
size_t p_size = 256;
//char entropy[ent];
int i;
char prime[p_size];
srand(time(NULL)); // feed the machine
for(i=0;i<2;i++) {
    if(l_rand_entropy(ent, entropy)) {
        printf("Entropy: %s\n", entropy);
    }
}
for(i=0;i<5;i++) {
    l_prime(p_size, prime, 0);
    printf("%s\n\n", prime);
}
```

## testing

### valgrind

```bash
clear;make clean;make;valgrind --track-origins=yes ./lol
clear;make clean;make;valgrind --suppressions=/home/levi/valgrind.suppressions ./lol
```

### top

```bash
top -b -n 1 |grep lol
```

## useful links

* https://computing.llnl.gov/tutorials/pthreads/
* http://www.asciitable.com/index/asciifull.gif
* http://stackoverflow.com/questions/2426277/how-free-works-when-pointer-is-incremented
* http://stackoverflow.com/questions/1963780/when-should-i-use-malloc-in-c-and-when-dont-i
* http://www.cs.bu.edu/teaching/cpp/string/array-vs-ptr/
* https://wiki.openssl.org/index.php/Main_Page
