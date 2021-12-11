#include "node.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//NOde adt
//left = left child node
//right - right child node
//symbol = symbol
//frequency = frequency
Node *node_create(uint8_t symbol, uint64_t frequency) {
    Node *n = (Node *) malloc(sizeof(Node));
    if (n) {
        n->left = NULL;
        n->right = NULL;
        n->symbol = symbol;
        n->frequency = frequency;
    }
    return n;
}

void node_delete(Node **n) {
    if (*n) {
        free(*n);
        *n = NULL;
    }
}

//Makes a join node from 2 child nodes
Node *node_join(Node *left, Node *right) {
    Node *result = node_create('$', left->frequency + right->frequency);
    result->left = left;
    result->right = right;
    return result;
}

void node_print(Node *n) {
    if (n == NULL) {
        return;
    }

    node_print(n->left);

    node_print(n->right);
    if (n->left == NULL && n->right == NULL) {

        printf("L%u", n->symbol);
    } else {
        printf("I");
    }
}
/*
int main(void){
	Node *root = node_create(0,0);
	root->left = node_create(1,0);
	root->right = node_create(2,0);
	root->left->left = node_create(3,0);
	root->left->right = node_create(4,0);
	root->right->left = node_create(5,0);
	root->right->right = node_create(6,0);
	node_print(root);
	return 0;
}
*/
