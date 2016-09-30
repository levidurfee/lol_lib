# lol lib

> old code had a lot of memory leaks, so i am redoing it from scratch, testing it as i go

i've been reading books on C that will hopefully help me develop a more solid library.

## testing

### valgrind

```bash
clear;make clean;make;valgrind --track-origins=yes ./lol
```

### top

```bash
top -b -n 1 |grep lol
```

## useful links

* http://www.asciitable.com/index/asciifull.gif
* http://stackoverflow.com/questions/2426277/how-free-works-when-pointer-is-incremented
* http://stackoverflow.com/questions/1963780/when-should-i-use-malloc-in-c-and-when-dont-i
* http://www.cs.bu.edu/teaching/cpp/string/array-vs-ptr/
