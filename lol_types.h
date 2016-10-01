typedef struct {
    int max;            // max amount of loops?
    int cur;            // current iteration
    char *data;         // data for the function pointer
    int tid;            // thread id
} lol_arg;

lol_arg *lol_arg_new(int max, int cur, char *data, int tid);
lol_arg *lol_arg_copy(lol_arg const *in);
void lol_arg_free(lol_arg *in);