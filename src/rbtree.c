#include "rbtree.h"

#include <stdlib.h>

void insert_fixup(rbtree *t, node_t *n);
void left_rotate(rbtree *t, node_t *n);
void right_rotate(rbtree *t, node_t *n);

void rb_transplant(rbtree *t, node_t *u, node_t *v);
node_t *sub_rbTree_min(rbtree *t, node_t *n);
void rb_delete_fixup(rbtree *t, node_t *n);
void insert_arr(rbtree *t, const key_t *arr, const size_t n);
int dfs_tree(const rbtree *t, node_t *n,key_t *arr, int index);

int delete_node(rbtree *t, node_t *node);

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(2, sizeof(rbtree));
  node_t *nilNode = (node_t *)calloc(10, sizeof(node_t));
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
  node_t *root_node = t->root;
  delete_node(t,root_node);
  free(t->nil);
  free(t);
}

int delete_node(rbtree *t, node_t *node){
  if(node == t->nil){
    return 0;
  }

  delete_node(t,node->left);
  delete_node(t,node->right);

  free(node);
  return 0;
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
  t->root->parent = t->nil;
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
  node_t *search_node = t->root;
  while(search_node != t->nil){
    if(search_node->key == key){
      break;
    }
    else if(search_node->key > key){
      search_node = search_node->left;
    }
    else{
      search_node = search_node->right;
    }
  }
  if (search_node == t->nil){
    return NULL;
  }
  return search_node;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  node_t *min_node = t->root;
  while(min_node->left != t->nil){
    min_node = min_node->left;
  }
  return min_node;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  node_t *max_node = t->root;
  while(max_node->right != t->nil){
    max_node = max_node->right;
  }
  return max_node;
}

int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase
  node_t *y = p;
  color_t eNodeOri_C = p->color;
  node_t *x = p->right;
  if(p->left == t->nil){
    x = p->right;
    rb_transplant(t,p,p->right);
  }
  else if(p->right == t->nil){
    x = p->left;
    rb_transplant(t,p,p->left);
  }
  else{
    y = sub_rbTree_min(t,p->right);
    eNodeOri_C = y->color;
    x = y->right;
    if(y->parent == p){
      x->parent = y;
    }
    else{
      rb_transplant(t,y,y->right);
      y->right = p->right;
      y->right->parent = y;
    }
    rb_transplant(t,p,y);
    y->left = p->left;
    y->left->parent = y;
    y->color = p->color;
  }

  if(eNodeOri_C == RBTREE_BLACK){
    rb_delete_fixup(t,x);
  }
  t->root->parent = t->nil;
  free(p);
  return 0;
}

node_t *sub_rbTree_min(rbtree *t, node_t *n){
  node_t *sub_min_node = n;
  while(sub_min_node->left != t->nil){
    sub_min_node = sub_min_node->left;
  }
  return sub_min_node;
}

void rb_transplant(rbtree *t, node_t *u, node_t *v){
  if(u->parent == t->nil){
    t->root = v;
  }
  else if(u == u->parent->left){
    u->parent->left = v;
  }
  else{
    u->parent->right = v;
  }
  v->parent = u->parent;
}

void rb_delete_fixup(rbtree *t, node_t *n){
  while( n != t->root && n->color == RBTREE_BLACK){
    if(n == n->parent->left){
      node_t *w = n->parent->right;
      if(w->color == RBTREE_RED){
        w->color = RBTREE_BLACK;
        n->parent->color = RBTREE_RED;
        left_rotate(t,n->parent);
        w = n->parent->right;
      }
      if(w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK){
        w->color = RBTREE_RED;
        n = n->parent;
      }
      else{
        if(w->right->color == RBTREE_BLACK){
          w->left->color = RBTREE_BLACK;
          w->color = RBTREE_RED;
          right_rotate(t,w);
          w = n->parent->right;
        }
        w->color = n->parent->color;
        n->parent->color = RBTREE_BLACK;
        w->right->color = RBTREE_BLACK;
        left_rotate(t,n->parent);
        n = t->root;
      } 
    }
    else{
      node_t *w = n->parent->left;
      if(w->color == RBTREE_RED){
        w->color = RBTREE_BLACK;
        n->parent->color = RBTREE_RED;
        right_rotate(t,n->parent);
        w = n->parent->left;
      }
      if(w->right->color == RBTREE_BLACK && w->left->color == RBTREE_BLACK){
        w->color = RBTREE_RED;
        n = n->parent;
      }
      else{
        if(w->left->color == RBTREE_BLACK){
          w->right->color = RBTREE_BLACK;
          w->color = RBTREE_RED;
          left_rotate(t,w);
          w = n->parent->left;
        }
        w->color = n->parent->color;
        n->parent->color = RBTREE_BLACK;
        w->left->color = RBTREE_BLACK;
        right_rotate(t,n->parent);
        n = t->root;
      }
    }
  }
  n->color = RBTREE_BLACK;
}

void insert_arr(rbtree *t, const key_t *arr, const size_t n){
  for(int i=0;i<n;i++){
    rbtree_insert(t,arr[i]);
  }
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  dfs_tree(t,t->root,arr,0);
  return 0;
}

int dfs_tree(const rbtree *t, node_t *n,key_t *arr, int index){
  if(n->left != t->nil){
    index = dfs_tree(t,n->left,arr,index);
  }

  arr[index] = n->key;
  index ++;

  if(n->right != t->nil){
    index = dfs_tree(t,n->right,arr,index);
  }

  return index;
}
