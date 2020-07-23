#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/**
 * -Full binary tree/Proper Binary Tree
 * - Theorems:
 *         - if i = number of internal nodes, l = number of leaves and n = total number of nodes;
 *         - Total number of leaves can be given by: l = i + 1, l = (n+1)/2
 *         - Total number of internal nodes: i = l - 1, (n-1)/2
 *         - Total number of nodes: n = 2l-1, 2i+1
*/
struct node {
    int item;
    struct node *left;
    struct node *right;
};
struct node *createNode(int item) {
    struct node *newNode = malloc(sizeof(struct node));
    newNode->item = item;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
bool isFullBinaryTree(struct node *root) {
    if(root == NULL)
        return true;
    if(root->left == NULL && root->right == NULL)
        return true;
    if(root->left && root->right)
        return (isFullBinaryTree(root->left) && isFullBinaryTree(root->right));
    return false;
}
int main() {
    struct node *root = createNode(1);
    root->left  = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->left->right->left = createNode(6);
    root->left->right->right = createNode(7);
    if(isFullBinaryTree(root)) {
        printf("Is a full binary tree\n");
    } else {
        printf("Not a binary tree\n");
    }
    return 0;
}