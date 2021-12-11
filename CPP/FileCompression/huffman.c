#include "huffman.h"

#include "defines.h"
#include "pq.h"
#include "stack.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

Code c = { 0, { 0 } };

Node *build_tree(uint64_t hist[static ALPHABET]) {
    PriorityQueue *pq = pq_create(ALPHABET);
    if (hist[0] == hist[255]) {
        enqueue(pq, node_create(0, hist[0]));
        enqueue(pq, node_create(255, hist[255]));
        for (int i = 1; i < 255; i++) {
            if (hist[i] != 0) {
                Node *newNode = node_create(i, hist[i]);
                enqueue(pq, newNode);
            }
        }
    } else {
        for (int i = 0; i < 256; i++) {
            if (hist[i] != 0) {
                Node *newNode = node_create(i, hist[i]);
                enqueue(pq, newNode);
            }
        }
    }

    //pq_print(pq);
    //printf("\n");
    Node *left = NULL;
    Node *right = NULL;
    while (pq_size(pq) > 1) {
        //printf("pq_size, %u\n", pq_size(pq));
        dequeue(pq, &left);
        dequeue(pq, &right);
        enqueue(pq, node_join(left, right));
    }
    Node *result;
    dequeue(pq, &result);
    pq_delete(&pq);
    return (result);
}

void build_codes(Node *root, Code table[static ALPHABET]) {
    uint8_t uselessBit = 0;
    if (root->left == NULL && root->right == NULL) {
        table[root->symbol] = c;
    } else {
        code_push_bit(&c, 0);
        build_codes(root->left, table);
        code_pop_bit(&c, &uselessBit);

        code_push_bit(&c, 1);
        build_codes(root->right, table);
        code_pop_bit(&c, &uselessBit);
    }
}

Node *rebuild_tree(uint16_t nbytes, uint8_t tree[static nbytes]) {
    bool leaf = false;
    Stack *treeStack = stack_create(nbytes);
    for (int x = 0; x < nbytes; x++) {
        if (leaf == false && tree[x] == 'L') {
            leaf = true;
        } else if (leaf) {
            Node *newNode = node_create(tree[x], 1);
            stack_push(treeStack, newNode);
            leaf = false;
        } else if (tree[x] == 'I') {
            Node *right = NULL;
            Node *left = NULL;
            stack_pop(treeStack, &right);
            stack_pop(treeStack, &left);
            stack_push(treeStack, node_join(left, right));
        }
    }
    Node *resultNode;
    stack_pop(treeStack, &resultNode);
    return (resultNode);
}

void delete_tree(Node **root) {
    if ((*root)->left != NULL) {
        delete_tree(&(*root)->left);
    }
    if ((*root)->right != NULL) {
        delete_tree(&(*root)->right);
    }
    node_delete(root);
}
/*
int main(){
	printf("Rebuilding Tree \n");
	int size = 17;
	uint8_t treeDump[17];
	treeDump[0] = 'L';
	treeDump[1] = 's';
	treeDump[2] = 'L';
	treeDump[3] = 't';
	treeDump[4] = 'I';
	treeDump[5] = 'L';
	treeDump[6] = 'a';
	treeDump[7] = 'L';
	treeDump[8] = 'e';
	treeDump[9] = 'I';
	treeDump[10] = 'L';
	treeDump[11] = 'h';
	treeDump[12] = 'I';
	treeDump[13] = 'L';
	treeDump[14] = 'i';
	treeDump[15] = 'I';
	treeDump[16] = 'I';
	Node *root = rebuild_tree(size, treeDump);
	node_print(root);
	printf("\n");
	printf("%u\n", root->left->left->symbol);
	printf("%u\n", root->left->right->symbol);
	return 1;
}
*/
