#include "structs.h"
#include <stdio.h>

Node *newNode(Product product);
int height(Node *node);
int max(int a, int b);
Node *rightRotate(Node *y);
Node *leftRotate(Node *x);
int getBalance(Node *node);
Node *minValueNode(Node *node);
Node *deleteNode(Node *root, Product product);
Node *insert(Node *node, Product product);
int returnBiggestId(Node *root);
void inOrder(Node *root);
void printTree(Node *root, int desloc);
Node *searchForId(Node *node, int id);

Node *insertOrderName(Node *node, Product product);
void printTreeOrder(Node *root, int desloc);
void inOrderTree(Node *root);
void printTreeToFile(Node *root, FILE *file, double *total);
