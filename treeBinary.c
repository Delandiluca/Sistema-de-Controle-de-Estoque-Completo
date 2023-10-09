#include "treeBinary.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Node *newNode(Product product) {
  Node *node = (Node *)malloc(sizeof(Node));
  node->product = product;
  node->left = NULL;
  node->right = NULL;
  node->height = 1;
  return node;
}

// Função para obter a altura da árvore
int height(Node *node) {
  if (node == NULL)
    return 0;
  return node->height;
}

// Função para obter o máximo de dois inteiros
int max(int a, int b) { return (a > b) ? a : b; }

// Rotação a direita no y
Node *rightRotate(Node *y) {
  Node *x = y->left;
  Node *T2 = x->right;

  // faz a rotação
  x->right = y;
  y->left = T2;

  // atualiza a altura
  y->height = max(height(y->left), height(y->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;

  // retorna a nova raiz
  return x;
}

// rotação a direita de x
Node *leftRotate(Node *x) {
  Node *y = x->right;
  Node *T2 = y->left;

  // faz a rotação
  y->left = x;
  x->right = T2;

  //  atualiza a altura
  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;

  // Retorna a nova Raiz
  return y;
}

// Função para obter o fator de balanceamento de um nó N
int getBalance(Node *node) {
  if (node == NULL)
    return 0;
  return height(node->left) - height(node->right);
}

Node *minValueNode(Node *node) {
  Node *current = node;
  /* loop para encontrar o nó mais a esquerda */
  while (current && current->left != NULL)
    current = current->left;
  return current;
}

Node *insert(Node *node, Product product) {
  /* 1. Realiza a inserção normal de BST */
  if (node == NULL)
    return (newNode(product));

  if (product.id < node->product.id)
    node->left = insert(node->left, product);
  else if (product.id > node->product.id)
    node->right = insert(node->right, product);
  else // IDs iguais não são permitidos na BST
    return node;

  /* 2. Atualiza a altura do nó ancestral */
  node->height = 1 + max(height(node->left), height(node->right));

  /* 3. Obtém o fator de balanceamento deste nó raiz para verificar se este nó
   * se tornou desbalanceado */
  int balance = getBalance(node);

  // Se este nó se torna desbalanceado, então há 4 casos:
  // Caso esquerda esquerda
  if (balance > 1 && product.id < node->left->product.id)
    return rightRotate(node);

  // Caso direita direita
  if (balance < -1 && product.id > node->right->product.id)
    return leftRotate(node);

  // Caso esquerda direita
  if (balance > 1 && product.id > node->left->product.id) {
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }

  // Caso direita esquerda
  if (balance < -1 && product.id < node->right->product.id) {
    node->left = rightRotate(node->right);
    return leftRotate(node);
  }

  /* retorna o ponteiro do nó (inalterado) */
  return node;
}

// Função que apaga uma Chave da BST e retorna uma nova raiz
Node *deleteNode(Node *root, Product product) {
  if (root == NULL)
    return root;

  // testa se a chave buscada é menor que a raiz "atual"
  if (product.id < root->product.id) {
    root->left = deleteNode(root->left, product);
  }
  // testa se a chave buscada é maior que a "raiz"
  else if (product.id > root->product.id) {
    root->right = deleteNode(root->right, product);
  }
  // se a chave for igual ao dado do nó raiz, esse será apagado
  else {
    // Caso II: O nó a ser eliminado tem uma subárvore a direita
    if (root->left == NULL) {
      Node *temp = root->right;
      free(root);
      return temp;
    }
    // Caso III: O nó a ser eliminado tem uma subárvore a esquerda
    else if (root->right == NULL) {
      Node *temp = root->left;
      free(root);
      return temp;
    }

    // Caso IV: O nó a ser eliminado tem duas subárvores
    //  Pega o Sucessor em inorder (menor da subarvore direita)
    Node *temp = minValueNode(root->right);
    // copia o conteúdo do sucessor em inorder para esse nó
    root->product.id = temp->product.id;
    // Apaga o sucessor em inorder
    root->right = deleteNode(root->right, temp->product);
  }

  // if(root == NULL){
  // return root; //Se foi o último nó que havia removido!!
  //}

  /* 2. Atualiza a altura do nó ancestral */
  root->height = 1 + max(height(root->left), height(root->right));

  /* 3. Obtém o fator de balanceamento deste nó raiz para verificar se este nó
   * se tornou desbalanceado */
  int balance = getBalance(root);

  // Se este nó se torna desbalanceado, então há 4 casos:
  // Caso esquerda esquerda
  if (balance > 1 && product.id < root->left->product.id)
    return rightRotate(root);

  // Caso direita direita
  if (balance < -1 && product.id > root->right->product.id)
    return leftRotate(root);

  // Caso esquerda direita
  if (balance > 1 && product.id > root->left->product.id) {
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }

  // Caso direita esquerda
  if (balance < -1 && product.id < root->right->product.id) {
    root->left = rightRotate(root->right);
    return leftRotate(root);
  }

  return root;
}

int returnBiggestId(Node *root) {
  if (root == NULL) {
    return 0;
  }

  if (root->right != NULL) {
    return returnBiggestId(root->right);
  } else {
    return root->product.id;
  }
}

// Função para buscar um produto por Id na árvore AVL
Node *searchForId(Node *node, int id) {
  if (node == NULL || node->product.id == id)
    return node;

  if (id < node->product.id)
    return searchForId(node->left, id);

  return searchForId(node->right, id);
}

// impressão da árvore e das alturas dos nós
void printTree(Node *root, int desloc) {
  if (root == NULL)
    return;
  printTree(root->right, desloc + 3);
  printf("%*s%d %d %s\n", desloc, "", root->product.id, root->product.quantity, root->product.name);
  printTree(root->left, desloc + 3);
}

void inOrder(Node *root) {
  if (root == NULL)
    return;
  inOrder(root->left);
  printf("\n%d", root->product.id);
  inOrder(root->right);
}

// FUNÇÕES ÁRVORE AVL ORGANIZADA POR ORDEM ALFABETICA PELO NOME
Node *insertOrderName(Node *node, Product product) {
  if (node == NULL)
    return (newNode(product));

  // Função que compara strings
  int compareResult = strcmp(product.name, node->product.name);

  if (compareResult < 0)
    node->left = insertOrderName(node->left, product);

  else if (compareResult > 0)
    node->right = insertOrderName(node->right, product);

  else
    return node;

  /*
  node->height = 1 + max(height(node->left), height(node->right));

  int balance = getBalance(node);

  if (balance > 1 && getBalance(node->left) >= 0)
    return rightRotate(node);

  if (balance < -1 && getBalance(node->right) <= 0)
    return leftRotate(node);

  if (balance > 1 && getBalance(node->left) < 0)
    node->left = leftRotate(node->left);
  return rightRotate(node);

  if (balance < -1 && getBalance(node->right) > 0)
    node->right = rightRotate(node->right);
  return leftRotate(node);
  */

  return node;
}

void printTreeOrder(Node *root, int desloc) {
  if (root == NULL)
    return;
  printTreeOrder(root->right, desloc + 3);
  printf("%*s%s\n", desloc, "", root->product.name);
  printTreeOrder(root->left, desloc + 3);
}

void inOrderTree(Node *root) {
  if (root == NULL)
    return;
  inOrderTree(root->left);
  printf("%s ", root->product.name);
  inOrderTree(root->right);
}

void printTreeToFile(Node *root, FILE *file, double *total) {
  if (root != NULL) {
    printTreeToFile(root->left, file, total);
    double value = (root->product.cost * root->product.quantity);
    *total += value;
    fprintf(file, "  %-5d %-23s %-8d R$%-7.2lf R$%-7.2lf R$%.2lf\n",
            root->product.id, root->product.name, root->product.quantity,
            root->product.priceSale, root->product.cost, value);
    printTreeToFile(root->right, file, total);
  }
}