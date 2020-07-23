#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 * All internal nodes in a binary search tree have exactly two children
 * All nodes of the left subtree are less than root
 * All nodes of the right subtree are greater than root
 * We will look at insertion, search and delete operations
*/
struct node {
    int key;
    struct node *left, *right;
};
// create a new node
struct node *createNode(int key) {
    struct node *root = malloc(sizeof(struct node ));
    root->key = key;
    root->left = root->right = NULL;
    return root;
}
// insert a node
struct node *insertNode(struct node *node,int item) {
    if(node == NULL)
        return createNode(item);
    // traverse to the right subtree and insert node
    if(item < node->key)
        node->left = insertNode(node->left, item);
    else
    {
        node->right = insertNode(node->right, item);
    }
    return node;
}
// Find the inorder successor of a tree
struct node *inOrderSuccessor(struct node *node) {
    if(!node)
        return NULL;
    struct node *minNode = node;
    while(minNode && minNode->left) {
        minNode = minNode->left;
    }
    return minNode;
}
/**
 * Delete operation for a BST has three scenarios:
 *  - The node to be deleted is a leaf node, in such a case, simply delete the  node from tree
 *  - The node to be deleted has only one child; replace the node to be deleted with the child and free the child node
 *  - The node to be deleted has two children; find the in-order successor of the right child, replace th node with the inorder successor and delete successor node from its position
*/
struct node *deleteNode(struct node *root, int key) {
    // if the BST is empty, return 
    if(!root)
        return root;
    // Find the node to be deleted recursively
    if(key < root->key) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    } else {
        // if the node has only one child or no child
        if(root->left == NULL) {
            struct node *temp = root->right;
            free(root);
            return temp;
        } else if(root ->right == NULL) {
            struct node *temp = root->left;
            free(root);
            return temp;
        }
        // If the node to be deleted has two children, find the in-order successor of the right child
        struct node *temp = inOrderSuccessor(root->right);
        root->key = temp->key;
        // delete the inorder successor
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}
// perform in-order traversal
void inorderTraversal(struct node *root) {
    if(root == NULL)
        return;
    inorderTraversal(root->left);
    printf("%d -> ", root->key);
    inorderTraversal(root->right);
    printf("\n");
}
int main() {
    struct node *root = NULL;
    root = insertNode(root,1);
    root = insertNode(root,3);
    root = insertNode(root,4);
    root = insertNode(root,6);
    root = insertNode(root,7);
    root = insertNode(root,8);
    root = insertNode(root,10);
    root = insertNode(root,14);
    inorderTraversal(root);
    deleteNode(root, 3);
    inorderTraversal(root);
    return 0;
}