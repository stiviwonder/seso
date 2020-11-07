#include <stdio.h>
#include <stdlib.h>
#include "../include/global.h"

volatile node_t* leftmost;

node_t* new_node(int vruntime, struct process p, node_t* dad){
    node_t* n;
    n = malloc(sizeof(node_t));

    n->vruntime = vruntime;
    n->process = p;
    n->dadi = dad; // esto seguro que hay que hacer cpy o algo asi
    n->left = NULL;
    n->right = NULL;

    return n;
} 

node_t* find_minimum(node_t* root){
    if (root == NULL)
	return NULL;
    // El nodo minimo no tendra nada en la left.
    else if (root->left != NULL)
	return find_minimum(root->left);
    return root;
}

/**
 * TODO: actualizar el leftmost cuando inserte uno mas pequeño
 */
node_t* insert(node_t* root, int x, struct process p, node_t* dad){

    // Busca el lugar para insert
    if (root == NULL){
	node_t* n = new_node(x, p, dad);
//	if (x < leftmost->vruntime)
//	    leftmost = n;
	return n;
    }
    else if (x > root->vruntime)
       root->right = insert(root->right, x, p, root);
    else 
	root->left = insert(root->left, x, p, root);
    return root;
}
/**
 * TODO: actualizar el leftmost cuando se borre
 */
node_t* delete(node_t* root, int x){

    // Busca el nodo que deletear
    if (root == NULL)
	return root;
    if (x > root->vruntime)
       root->right = delete(root->right, x);
    else if (x < root->vruntime)
       root->left = delete(root->left, x);
    else{

	// No children
	if (root->left == NULL && root->right == NULL){
//	    if (root->vruntime == leftmost->vruntime)
//		leftmost = root->dadi;
	    free(root);
	    return NULL;
	}

	// One child
	else if (root->left == NULL || root->right == NULL){
	    node_t* temp;
	    if (root->left == NULL){
		temp = root->right;
//		if (root->vruntime == leftmost->vruntime)
//		    leftmost = temp;
	    }
	    else
		temp = root->left;
	    free(root);
	    return temp;
	}

	// Two children
	else{
	    node_t* temp = find_minimum(root->right);
	    root->vruntime = temp->vruntime;
	    root->process = temp->process;
	    root->dadi = temp->dadi;
	    root->right = delete(root->right, temp->vruntime);
	}


    }
    return root;


}

void print_tree(node_t* root){
    if (root != NULL){
	print_tree(root->left);
	printf(" %d ", root->vruntime);
	print_tree(root->right);
    }
}
