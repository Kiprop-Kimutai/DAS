#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"
#define T 3 // degree of the tree
struct node {
    int n; // number of keys
    bool leaf; // leafness of a node
    struct node **children;
    int *keys;
};
struct node *root;
struct node *createNode(int key);
void insertKey(struct node *node,int key);
void splitNode(int insertAt, struct node *parent, struct node *child);
void insertNonFull(struct node * root,  int key);
void inOrderTraversal(struct node *root );
int main() {
    root = createNode(10);
    insertKey(root, 50);
    insertKey(root, 20);
    insertKey(root, 30);
    insertKey(root, 70);
    insertKey(root, 40);
    insertKey(root, 60);
    insertKey(root, 20);
    inOrderTraversal(root);
    printf("\n");
    return 0;
}
struct node *createNode(int key) {
    struct node *root = malloc(sizeof(struct node));
    root->children = malloc((2*T)*(sizeof(struct node)));
    root->keys = malloc((2*T-1)*sizeof(int));
    if(root == NULL) {
        printf("Memory exhausted\n");
        return NULL;
    } else
    {
         root->leaf = true;
         root->keys[0] = key;
         root->n = 1;
         return root;
    }
}
void insertKey(struct node *node,int key) {
    printf("N:%d\n", node->n);
    inOrderTraversal(node);
    if(node == NULL) {
        node = createNode(key);
    } else { // if tree is not empty
        // if node is full
        if(node->n == (2*T)-1) {
            // create new node
            printf("--------\n");
            struct node *newroot = (struct node *)malloc(sizeof(struct node));
            newroot->children = malloc((2*T)*(sizeof(struct node)));
            newroot->keys = malloc((2*T-1)*(sizeof(int)));
            newroot->children[0] = node;
            newroot->leaf = false;
            // split node into two
            splitNode(0,  newroot, newroot->children[0]);
            int i = 0;
            if(newroot->keys[i] < key) {
                i++;
            }
            // insertnonFull(newroot->children[i], int key,)
            insertNonFull(newroot->children[i],key);
            // make newroot the root
            root = newroot;
        } else {
            insertNonFull(node, key);
        }
    }
}
// all nodes coming here are assumed to be non-full
void insertNonFull(struct node * node,  int key) {
    int i = node->n-1;
    // if root is leaf, insert key otherwise find the child node where the key goes
    if(node->leaf) {
        if(key == 60) {
            printf("watching...\n");
            printf("N:%d->\n",node->keys[0]);
            inOrderTraversal(node);
        }
        // create space in root for the new key
        i = node->n-1;
        while(node->keys[i] > key && i >= 0 ) {
            node->keys[i+1] = node->keys[i];
            i--;
        }
        node->keys[i+1] = key;
        node->n = node->n+1;
        printf("kaput\n");
    } else { // if the node is non-leaf, find which child node is going to have the key
        while(node->keys[i] > key && i >= 0) {
            i--;
        }
        // if the found node is full, split it
        if(node->children[i+1]->n == (2*T-1)) {
            splitNode(i+1, node, node->children[i+1]);
            int j = i+1;
            if(node->keys[i+1] < key) {
                i++;
            }
        }
        insertNonFull(node->children[i+1], key);
    }
}
void splitNode(int insertAt,struct node *parent, struct node *child) {
    printf("splitting...\n");
    int j;
    struct node *sibling = malloc(sizeof(struct node));
    sibling->children = malloc((2*T)*(sizeof(struct node)));
    sibling->keys = malloc((2*T-1)*(sizeof(int)));
    sibling->leaf = true;
    child->leaf = true;
    // copy the last T-1 keys from child to sibling
    for(j = 0; j < T-1; j++) {
        sibling->keys[j] = child->keys[j+T];
    }
    // if child node is non-leaf, copy its last T children to sibling
    for(j = 0; j < T; j++) {
        sibling->children[j] = child->children[j+T];
    }
    // set n values for sibling and child
    sibling->n = T-1;
    child->n = T-1;
    // median key from child is going to move up to parent node. Create space for it in parent
    for(j = parent->n-1; j >= insertAt; j--) {
        parent->keys[j+1] = parent->keys[j]; 
    }
    parent->keys[insertAt] = child->keys[T-1];
    for(int j = parent->n; j >= insertAt+1; j--) {
        parent->children[j+1] = parent->children[j];
    }
    parent->children[insertAt+1] = sibling;
    parent->n = parent->n+1;
    printf("---done----\n");
}
void inOrderTraversal(struct node *root) {
  if(root == NULL)
    printf("Tree is empty\n");
  else {
    int i;
    for(i = 0; i < root->n; i++) {
      if(!root->leaf) {
        // traverse child rooted at i 
        inOrderTraversal(root->children[i]);
      }
      printf("%d->",root->keys[i]);
    }
    // print contents of child rooted with the last key
    if(!root->leaf) {
      inOrderTraversal(root->children[i]);
    }
  }
}