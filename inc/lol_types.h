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

struct bin_tree {
    int data;
    struct bin_tree *right, *left;
};

typedef struct bin_tree node;

void insert(node **tree, int val);
void print_preorder(node *tree);
void print_inorder(node *tree);
void print_postorder(node *tree);
void deltree(node *tree);
node *search(node **tree, int val);
#endif
