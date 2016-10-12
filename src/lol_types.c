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

    if(val < (*tree)->data) {
        insert(&(*tree)->left, val);
    } else if(val > (*tree)->data) {
        insert(&(*tree)->right, val);
    }
}

void print_preorder(node *tree) {
    if(tree) {
        printf("%d\n", tree->data);
        print_preorder(tree->left);
        print_preorder(tree->right);
    }
}

void print_inorder(node *tree) {
    if(tree) {
        print_inorder(tree->left);
        printf("%d\n", tree->data);
        print_inorder(tree->right);
    }
}

void print_postorder(node *tree) {
    if(tree) {
        print_postorder(tree->left);
        print_postorder(tree->right);
        printf("%d\n", tree->data);
    }
}

void deltree(node *tree) {
    if(tree) {
        deltree(tree->left);
        deltree(tree->right);
        free(tree);
    }
}

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
