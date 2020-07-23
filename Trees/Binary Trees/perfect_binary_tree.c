#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/**
 * - Perfect Binary tree theorems:
 *  - A perfect binary tree of height h has (h^height+1)-1 nodes
 *  - A perfect binary tree with nodes n has height log(n+1)-1
 *  - A perfect binary tree of height h has 2^h leaf nodes
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
};
int find_depth(struct node *root) {
    int depth = -1;
    while(root != NULL) {
        depth++;
        root = root->left;
    }
    return depth;
}
bool is_perfect_binary_tree(struct node *root, int depth, int level) {
    if(root == NULL)
        return true;
    if(root->left == NULL && root->right == NULL)
        return (depth == level +1);
    if(root->left == NULL || root->right == NULL)
        return false;
    return (is_perfect_binary_tree(root->left, depth, level+1) && is_perfect_binary_tree(root->right, depth, level + 1));
}
int main() {
    struct node *root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);
    int depth = find_depth(root);
    bool isPerfect = is_perfect_binary_tree(root, depth, -1);
    if(isPerfect)
        printf("Is a perfect binary tree\n");
    else 
        printf("Not a perfect binary tree\n");
    return 0;
}