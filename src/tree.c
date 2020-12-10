#include <stdio.h>
#include <stdlib.h>
#include "../include/global.h"

/*====== GLOBAL VARIABLES ======*/

volatile node_t* leftmost;

/*====== FUNCTION IMPLEMENTATIONS ======*/

node_t* new_node(struct process p){
    node_t* n;
    n = malloc(sizeof(node_t));

    n->process = p;
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

node_t* insert(node_t* root, struct process p){

    int x = p.vruntime;

    // Zuhaitzan prozesua sartu
    if (root == NULL){
	node_t* n = new_node(p);
	if (x < leftmost->process.vruntime)
	    leftmost = n;
	return n;
    }

    // vruntime handiagoa bada eskubian lekua bilatu
    else if (x > root->process.vruntime)
       root->right = insert(root->right, p);

    // vruntime txikiagoa bada ezkerrean lekua bilatu
    else 
	root->left = insert(root->left, p);
    return root;
}
/**
 * TODO: actualizar el leftmost cuando se borre
 */
node_t* delete(node_t* root, int x){

    // Busca el nodo que deletear
    if (root == NULL)
	return root;
    if (x > root->process.vruntime)
       root->right = delete(root->right, x);
    else if (x < root->process.vruntime)
       root->left = delete(root->left, x);
    else{

	// No children
	if (root->left == NULL && root->right == NULL){
	    free(root);
	    return NULL;
	}

	// One child
	else if (root->left == NULL || root->right == NULL){
	    node_t* temp;

	    if (root->left == NULL){
		temp = root->right;
	    }
	    else
		temp = root->left;

	    free(root);
	    return temp;
	}

	// Two children
	else{
	    node_t* temp = find_minimum(root->right);
	    root->process = temp->process;
	    root->right = delete(root->right, temp->process.vruntime);
	}
    }
    return root;
}

void print_tree(node_t* root){
    if (root != NULL){
	print_tree(root->left);
	printf(" %d ", root->process.vruntime);
	print_tree(root->right);
    }
}
