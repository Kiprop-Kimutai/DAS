#include "stdio.h"
#include "stdlib.h"
/**
 * Inorder traversal: Left-Root->Right
 * Preorder traversal: Root->Left->Right
 * Postorder traversal: Left->Right->Root
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
void insertLeft(struct node *parent, int item) {
    if(!parent)
        return;
    parent->left = createNode(item);
}
void insertRight(struct node *parent, int item) {
    if(!parent)
        return;
    parent->right = createNode(item);
}
void inorderTraversal(struct node *root) {
    if(!root)
        return;
    inorderTraversal(root->left);
    printf("%d->",root->item);
    inorderTraversal(root->right);
}
void preorderTraversal(struct node *root) {
    if(!root)
        return;
    printf("%d->",root->item);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}
void postorderTraversal(struct node *root) {
    if(!root)
        return;
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    printf("%d->", root->item);
}
int main() {
    struct node *root = createNode(1);
    insertLeft(root,12);
    insertRight(root,9);
    insertLeft(root->left,5);
    insertRight(root->left, 6);
    inorderTraversal(root);
    printf("\n-----------------\n");
    preorderTraversal(root);
    printf("\n-----------------\n");
    postorderTraversal(root);
    printf("\n-----------------\n");
    return 0;
}