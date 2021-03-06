#ifndef tree_h
#define tree_h

#include "global.h"
node_t* new_node(struct process p);
node_t* find_minimum(node_t* root);
node_t* insert(node_t* root, struct process p);
node_t* delete(node_t* root, int x);
void print_tree(node_t* root);
#endif
