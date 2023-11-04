#include "rbtree.h"

#include <stdlib.h>

void insert_fixup(rbtree *t, node_t *n);
void left_rotate(rbtree *t, node_t *n);
void right_rotate(rbtree *t, node_t *n);

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  node_t *nilNode = (node_t *)calloc(1, sizeof(node_t));
  nilNode->color = RBTREE_BLACK;
  p -> nil = nilNode;
  p -> root = nilNode; 
  // TODO: initialize struct if needed
  return p;
}

node_t *new_node(key_t node_key){
  node_t *node = (node_t *)calloc(1, sizeof(node_t));
  node -> key = node_key;
  return node;
}

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  free(t);
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  node_t *node = (node_t *)calloc(1, sizeof(node_t));
  node->key = key;
  node->color = RBTREE_RED;
  node_t *y = t->nil;
  node_t *x = t->root;
  while(x != t->nil){
    y = x;
    if((node->key) < (x->key)){
      x = x->left;
    }
    else{
      x = x->right;
    }
  }
  node->parent = y;
  if(y == t->nil){
    t->root = node;
  }
  else if((node->key) < (y->key)){
    y->left = node;
  }
  else{
    y->right = node;
  }
  node->left = t->nil;
  node->right = t->nil;
  insert_fixup(t,node);
  // (t->root)->parent = t->nil;
  // TODO: implement insert
  return t->root;
}

void insert_fixup(rbtree *t, node_t *n){
  while(n->parent->color == RBTREE_RED){
    if(n->parent == n->parent->parent->left){
      node_t *y = n->parent->parent->right;
      if(y->color == RBTREE_RED){
        n->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        n->parent->parent->color = RBTREE_RED;
        n = n->parent->parent;
      }
      else {
        if(n == n->parent->right){
          n = n->parent;
          left_rotate(t,n);
        }
        n->parent->color = RBTREE_BLACK;
        n->parent->parent->color = RBTREE_RED;
        right_rotate(t,n->parent->parent);
      }  
    }
    else{
      node_t *y = n->parent->parent->left;
      if(y->color == RBTREE_RED){
        n->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        n->parent->parent->color = RBTREE_RED;
        n = n->parent->parent;
      }
      else{
        if(n == n->parent->left){
          n = n->parent;
          right_rotate(t,n);
        }
        n->parent->color = RBTREE_BLACK;
        n->parent->parent->color = RBTREE_RED;
        left_rotate(t,n->parent->parent);
      }
    }
  }
  t->root->color = RBTREE_BLACK;
}

void left_rotate(rbtree *t, node_t *n){
  node_t *y = n->right;
  n->right = y->left;
  if(y->left != t->nil){
    y->left->parent = n;
  }
  y->parent = n->parent;
  if(n->parent == t->nil){
    t->root = y;
  }
  else if(n == n->parent->left){
    n->parent->left = y;
  }
  else{
    n->parent->right = y;
  }
  y->left = n;
  n->parent = y;
}

void right_rotate(rbtree *t, node_t *n){
  node_t *y=n->left;
  n->left = y->right;
  if(y->right != t->nil){
    y->right->parent = n;
  }
  y->parent = n->parent;
  if(n->parent == t->nil){
    t->root = y;
  }
  else if(n == n->parent->right){
    n->parent->right = y;
  }
  else{
    n->parent->left = y;
  }
  y->right = n;
  n->parent = y;
}



node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}
