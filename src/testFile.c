#include "rbtree.c"

#include <stdio.h>
#include <stdlib.h>


int main(void){
    rbtree *tree = new_rbtree();
    
    printf("%s\n",(tree->nil->color == RBTREE_BLACK) ? "BLACK" : "RED");
    node_t *this_node = new_node(3);
    printf("%d\n",this_node->key);
    return 0;
}

