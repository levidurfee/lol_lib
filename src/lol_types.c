#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "lol_types.h"
/* lol_arg type functions */
lol_arg *lol_arg_new(size_t max, size_t cur, int tid, size_t bit) {
    lol_arg *out = malloc(sizeof(lol_arg));
    *out = (lol_arg) {.max = max, .cur = cur, .tid = tid, .bit = bit};
    return out;
}

lol_arg *lol_arg_copy(lol_arg const *in) {
    lol_arg *out = malloc(sizeof(lol_arg));
    *out = *in;
    return out;
}

void lol_arg_free(lol_arg *in) { free(in); }

/* binary tree */
void insert(node **tree, int val) {
    node *temp = NULL;
    if(!(*tree)) {
        temp = (node *)malloc(sizeof(node));
        temp->left = temp->right = NULL;
        temp->data = val;
        *tree = temp;
        return;
    }

    if(val < (*tree)->data) {               // if val less than data
        insert(&(*tree)->left, val);        // recursive function call
    } else if(val > (*tree)->data) {        // if val greater than data
        insert(&(*tree)->right, val);       // recursive function call
    }
}

/* show the order of the tree before ordering */
void print_preorder(node *tree) {
    if(tree) {
        printf("%d\n", tree->data);
        /* recursive function calls */
        print_preorder(tree->left);         // show left side of tree
        print_preorder(tree->right);        // then show right side of tree
    }
}

/* show the order of the tree asc */
void print_inorder(node *tree) {
    if(tree) {
        /* recursive function calls */
        print_inorder(tree->left);          // go down right side of tree
        printf("%d\n", tree->data);         // show the data
        print_inorder(tree->right);         // go down the right side
    }
}

/* show the order after it's in the tree */
void print_postorder(node *tree) {
    if(tree) {
        /* recursive function calls */
        print_postorder(tree->left);        // go down left side
        print_postorder(tree->right);       // go down right side
        printf("%d\n", tree->data);         // show the data
    }
}

/* go through the tree and free the nodes */
void deltree(node *tree) {
    if(tree) {
        /* recursive function calls */
        deltree(tree->left);                // del left side
        deltree(tree->right);               // del right side
        free(tree);
    }
}

/* 
search the tree for a specific value 
it will be faster to find values this way, than a linear list of
numbers. ex.

     11
   /    \
  06    19
 / \    / \
04 08  17 43
 \  \     / \
 05 10   31 49
 
Instead of going through all the numbers, eleven numbers, which could
take up to 11 comparisons. With the binary tree, it would take up to
4 comparisons.
*/
node *search(node **tree, int val) {
    if(!(*tree)) {
        return NULL;
    }

    if(val < (*tree)->data) {
        search(&((*tree)->left), val);
    } else if(val > (*tree)->data) {
        search(&((*tree)->right), val);
    } else if(val == (*tree)->data) {
        return *tree;
    }
    return NULL;
}
