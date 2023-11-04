#include "rbtree.c"

#include <stdio.h>
#include <stdlib.h>


int main(void){
    rbtree *tree = new_rbtree();
    
    printf("%s\n",(tree->nil->color == RBTREE_BLACK) ? "BLACK" : "RED");
    printf("%s\n",(tree->root == tree->nil) ? "BLACK" : "RED");
    node_t *this_node = rbtree_insert(tree,3);
    printf("%d\n",this_node->key);
    return 0;
}

