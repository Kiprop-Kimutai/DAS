#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

struct node {
    int key;
    struct node *left, *right;
};
// count number of nodes
int howManyNodes(struct node *root) {
    if(!root)
        return 0;
    while(root != NULL)
        return (1 +howManyNodes(root->left) + howManyNodes(root->right));
}
int main() {
    return 0;
}