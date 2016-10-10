#ifndef LOL_TYPES_H
#define LOL_TYPES_H
typedef struct {
    size_t max;         // max amount of loops?
    size_t cur;         // current iteration
    int tid;            // thread id
    size_t bit;         // bits
} lol_arg;

lol_arg *lol_arg_new(size_t max, size_t cur, int tid, size_t bit);
lol_arg *lol_arg_copy(lol_arg const *in);
void lol_arg_free(lol_arg *in);
#endif
