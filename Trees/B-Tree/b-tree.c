#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
// {most children =>2t keys => 2t-1 least children ->t, keys t-1}
#define T 3 // degree of the tree
struct BTreeNode {
  bool leaf; // leafness of a node 
  int n; // number of keys in a leaf
  struct BTreeNode **children;
  int *keys;
};
struct BTreeNode *root;

struct BTreeNode *createNode(int key);
void insertKey(int key);
void insertNonFull(struct BTreeNode *node, int key);
void splitNode(int splitAt, struct BTreeNode *parent);
void inorderTraversal(struct BTreeNode *node);
struct BTreeNode *search(struct BTreeNode *node, int key);
void deleteKey(struct BTreeNode *root, int key);
void deleteFromLeaf(struct BTreeNode *node, int index);
void deleteFromNonLeaf(struct BTreeNode *node, int index);
void removeKey(struct BTreeNode *node, int key);
int findKeyIndex(struct BTreeNode *node, int key);
void fill(struct BTreeNode *node, int key);
void borrowFromLeftSibling(struct BTreeNode *parentNode, int index);
void borrowFromRightSibling(struct BTreeNode *parentNode, int index);
void merge(struct BTreeNode *parentNode, int index);
int getPredecessor(struct BTreeNode *node, int index);
int getSuccessor(struct BTreeNode *node, int index);
int main(void) {
  printf("Hello World\n");
  insertKey(3);
  insertKey(4);
  insertKey(5);
  insertKey(6);
  insertKey(7);
  // insertKey(8);
  // insertKey(9);
  inorderTraversal(root);
  printf("\n");
  deleteKey(root,4);
  // inorderTraversal(root);
  return 0;
}
struct BTreeNode *createNode(int key) {
  struct BTreeNode *node = malloc(sizeof(struct BTreeNode *));
  node->children = malloc(2*T*(sizeof(struct BTreeNode *)));
  node->keys = malloc((2*T-1)*sizeof(int));
  node->keys[0] = key;
  node->n = 1;
  node->leaf = true;
  return node;
}
void insertKey(int key) {
  if(root == NULL) {
    root = createNode(key);
  } else {
    if(root->n == (2*T-1)) { // if root is full
      struct BTreeNode *newroot = malloc(sizeof(struct BTreeNode *));
      newroot->children = malloc((2*T)*sizeof(struct BTreeNode *));
      newroot->keys = malloc((2*T-1)*(sizeof(int)));
      newroot->n = 0;
      newroot->leaf = false;
      newroot->children[0] = root;
      // split child which is now full
      splitNode(0, newroot);
      printf("done splitting....\n");
      int i = 0;
      // determine which child is going to have the key
      if(newroot->keys[i] < key) {
        i++;
      }
      insertNonFull(newroot->children[i],key);
      root = newroot;
    } else {
      insertNonFull(root, key);
    }
  }
}
void insertNonFull(struct BTreeNode *node, int key) {
  int j = node->n-1;
  if(node->leaf) { // if node is a leaf, insert key here
    while(j >=0 && node->keys[j] > key) {
      node->keys[j+1] = node->keys[j];
      j--;
    }
    node->keys[j+1] = key;
    node->n++;
  } else { // if node is non-leaf, find the child which is to have the key
    while(node->keys[j] > key && j>=0) {
      j--;
    }
    // if node is full
    if(node->children[j+1]->n == (2*T-1)) {
      splitNode(j+1, node);
      if(node->keys[j+1] < key) {
        j++;
      }
    }
    insertNonFull(node->children[j+1], key);
  }
}
void splitNode(int insertAt, struct BTreeNode *parent) {
  struct BTreeNode *child = parent->children[insertAt];
  struct BTreeNode *sibling = malloc(sizeof(struct BTreeNode *));
  sibling->children = malloc((2*T)*(sizeof(struct BTreeNode *)));
  sibling->keys = malloc((2*T-1)*sizeof(int));

  sibling->leaf = child->leaf;
  printf("Sibling is a leaf %d\n", child->leaf);

  int j;
  // copy the last T-1 keys from child to sibling
  for(j = 0; j < T-1; j++) {
    sibling->keys[j] = child->keys[j+T];
  }
  // if child is non-leaf, copy the last T children from child to sibling
  if(!child->leaf) {
    for(j = 0; j < T; j++) {
      sibling->children[j] = child->children[j+T];
    }
  }

  // middle key in child is going to move up to parent. Create space in parent for this
  for(j = parent->n-1; j>=insertAt;j--) {
    parent->keys[j+1] = parent->keys[j];
  }
  parent->keys[insertAt] = child->keys[2];
  // create space in parent for the new child
  for(j = parent->n; j>=insertAt+1; j--) {
    parent->children[j+1] = parent->children[j];
  }
  parent->children[insertAt+1] = sibling;
  parent->n++;
    // update properties of both child nodes
  sibling->n = child->n = T-1;
}
void inorderTraversal(struct BTreeNode *node) {
  if(node == NULL) {
    printf("Node is empty\n");
  } else {
    int i;
    for(i = 0; i < node->n; i++) {
      if(!node->leaf)
        inorderTraversal(node->children[i]);
      printf("%d->", node->keys[i]);
    }
    if(!node->leaf)
      // print the node rooted with the last child
    inorderTraversal(node->children[i]);
  }
}
struct BTreeNode *search(struct BTreeNode *node, int key) {
  if(node == NULL)
    return NULL;
  int i = 0;
  while(i < node->n && node->keys[i] < key) {
    i++;
  }
  if(node->keys[i] == key) {
    return node;
  }
  // if key is not found and node is a leaf, return NULL
  if(node->leaf) {
    return NULL;
  }
  // if node is non-leaf, search the child rooted at this key
  return search(node->children[i], key);
}
int getPredecessor(struct BTreeNode *node, int index) {
  struct BTreeNode *child = node->children[index];
  while(!child->leaf) {
    child = child->children[child->n];
  }
  return child->keys[child->n];
}
int getSuccessor(struct BTreeNode *node, int index) {
  struct BTreeNode *child = node->children[index+1];
  while(!child->leaf) {
    child = child->children[0];
  }
  return child->keys[0];
}
void deleteFromLeaf(struct BTreeNode *node, int index) {
    printf("deleting from leaf...\n");
  inorderTraversal(node);
  for(int i = index+1; i < node->n; i++) {
    node->keys[i-1] = node->keys[i];
    printf("\nKey deleted from a leaf node\n");
  }
  node->n--;
}
void deleteFromNonLeaf(struct BTreeNode *node, int index) {
  if(node->children[index]->n >= T) {
    int predecessor = getPredecessor(node, index);
    node->keys[index] = predecessor;
    deleteKey(node->children[index], predecessor);
  } else if(node->children[index+1]->n >= T) {
    int successor = getSuccessor(node, index);
    node->keys[index] = successor;
    deleteKey(node->children[index+1], successor);
  } else {
    merge(node,index);
    removeKey(node->children[index], node->keys[index]);
  }
}
int findKeyIndex(struct BTreeNode *node, int key) {
  int index = 0;
  while(index < node->n && node->keys[index] < key) {
    index++;
  }
  return index;
}
void borrowFromLeftSibling(struct BTreeNode *parentNode, int index) {
  struct BTreeNode *child = parentNode->children[index];
  struct BTreeNode *leftsibling = parentNode->children[index-1];
  // create space in child for the new key from parent
  for(int j = 0; j < child->n; j++) {
      child->keys[j+1] = child->keys[j];
  }
  // key at position index-1 in parent goes down to become the first key in child
  child->keys[0] = parentNode->keys[index-1];
  // if child is a leaf, copy the last child of sibling to be first child of current child node
  if(!child->leaf) {
    for(int j = 0; j <= child->n; j++) {
      child->children[j+1] = child->children[j];
    }
    child->children[0] = leftsibling->children[leftsibling->n];
  }
  // increment number of children in child node
  child->n++;
  // last key in left sibling goes up to index-1 in parentNode
  parentNode->keys[index-1] = leftsibling->keys[leftsibling->n-1];
  // decrement number of keys in left sibling
  leftsibling->n--;
}
void borrowFromRightSibling(struct BTreeNode *parentNode, int index) {
    printf("Init...\n");
  struct BTreeNode *child = parentNode->children[index];
  struct BTreeNode *rightSibling = parentNode->children[index+1];
  // key at position index+1 inn parent goes down to become the last key in child node
  child->keys[child->n] = parentNode->keys[index];
  child->n++;
  // if child is a leaf node, copy the first child in right sibling to child node
  if(!child->leaf) {
    child->children[child->n] = rightSibling->children[0];
    // move all children from right sibling to one step back
    for(int j = 2; j < rightSibling->n; j++) {
      rightSibling->children[j-1] = rightSibling->children[j];
    }
  }
  // first key in right sibling goes up to replace key at position index in parent
  parentNode->keys[index] = rightSibling->keys[0];
  // move all keys in right sibling to one step behind
  for(int j = 1; j <= rightSibling->n; j++) {
    rightSibling->keys[j-1] = rightSibling->keys[j];
  }
  rightSibling->n--;
  printf("done...\n");

}
void merge(struct BTreeNode *parentNode, int index) {
  struct BTreeNode *leftChild = parentNode->children[index];
  struct BTreeNode *rightChild = parentNode->children[index+1];
  // key at positon index in node moves down to leftChild. Left child now has T keys
  leftChild->keys[0] = parentNode->keys[index];
  // copy all keys from right 
  for(int j = 0; j < rightChild->n; j++) {
    leftChild->keys[T+j] = rightChild->keys[j];
  }
  // if siblings are non-leafs, copy rightChild's children to leftChild
  if(!leftChild->leaf) {
    for(int j = 0; j < leftChild->n; j++) {
      leftChild->children[T+j] = rightChild->children[j];
    }
  }
  // move all keys after index in parentNode to one step before
  for(int j = parentNode->n-1; j >index; j--) {
    parentNode->keys[j-1] = parentNode->keys[j];
  }
  // move all children after rightChild to one step back
  for(int j = index+2; j <= parentNode->n; j++) {
    parentNode->children[j-1] = parentNode->children[j];
  }
  // set n values for leftChild and parentNode
  leftChild->n += rightChild->n + 1;
  parentNode->n --;
  free(rightChild);
}
// we are filling for child node at index
void fill(struct BTreeNode *node, int index) {
    printf("Filling....\n");
    printf("Index=>%d\n", index);
  if(index > 0 && node->children[index-1]->n >=T ) {
    borrowFromLeftSibling(node, index);
  } else if(node->children[index+1]->n >= T){
    borrowFromRightSibling(node,index);
  } else {
    if(index != node->n) {
      merge(node,index);
    } else {
      merge(node, index -1);
    }
  }
}
void removeKey(struct BTreeNode *node, int key) {
    printf("****\n");
 int index = findKeyIndex(node,key);
 printf("INDEX=>%d\n",index);
 printf("N=>%d\n",node->n);
 printf("LEAF => %d\n", node->leaf);

 // if key is found within this node
 if(index < node->n && node->keys[index] == key) {
     printf("Found key...");
   if(node->leaf)
      deleteFromLeaf(node,index);
   else
      deleteFromNonLeaf(node, index);
 } else {
     printf("Next node...\n");
   // if key is not found in this node and node is a leaf, then key is not there
   if(node->leaf) {
     printf("Key not found\n");
     return;
   }
   // the key to be deleted is rooted with the last child of this node
   int flag = (index == node->n) ? true: false;
   // if the last rooted child of this node has less than T keys, fill it
   if(node->children[index]->n < T) {
      fill(node, index);
   }
   if(flag && index > node->n) {
     removeKey(node->children[index-1], key);
   } else {
       printf("--->\n");
     removeKey(node->children[index], key);
   }
 }
}
void deleteKey(struct BTreeNode *root, int key) {
  if(root == NULL) {
    printf("Tree is empty\n");
  } else {
    removeKey(root, key);
    if(root->n == 0) {
      struct BTreeNode *temp = root;
      if(root->leaf) {
        root = NULL;
      } else {
      // make root's only child the new root
        root = root->children[0];
      }
      free(root);
    }
  }
}