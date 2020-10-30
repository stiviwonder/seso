#include <stdio.h>
#include <stdlib.h>
#include "global.h"

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
    if (root == NULL)
	return new_node(x, p, dad);
    else if (x > root->vruntime)
       root->right = insert(root->right, x, p, root);
    else 
	root->left = insert(root->left, root);
    return root;
}
/**
 * TODO: actualizar el leftmost cuando se borre
 */
node_t* delete(node_t* root, int x){

    // Busca el nodo que deletear
    if (root == NULL)
	return NULL;
    if (x > root->vruntime)
       root->right = delete(root->right, x);
    else if (x < root->vruntime)
       root->left = delete(root->right, x);
    else{

	// No children
	if (root->left == NULL && root->right == NULL){
	    free(root);
	    return NULL;
	}

	// One child
	else if (root->left == NULL || root->right == NULL){
	}

    }


}
