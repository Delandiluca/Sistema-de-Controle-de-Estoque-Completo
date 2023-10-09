#include "treeBinary.h"
#include <stdio.h>
#include <stdlib.h>

// Pega a altura da árvore
int height(Node *n) {
  if (n == NULL)
    return 0;
  return n->height;
}

void createTree(Node **root){
  *root = NULL;
}

// Pega o maior de dois inteiros
int max(int a, int b) { return (a > b) ? a : b; }

// retorna o fator de balancamento do nó n
int getBalance(Node *N) {
  if (N == NULL)
    return 0;
  return height(N->left) - height(N->right);
}

/* Aloca e inicializa um nó */
Node *newNode(Product *product) {
  Node *node = (Node *)malloc(sizeof(Node));
  node->product = product;
  node->left = NULL;
  node->right = NULL;
  node->height = 1; // nó inicializado adicionando uma folha
  return (node);
}

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

// inserção recursiva na árvore
// retornando uma nova raiz.
Node *insert(Node *node, Product *product) {
  // 1.  inserção normal na Árvore binária de busca
  if (node == NULL)
    return (newNode(product));

  if (product->id < node->product->id) {
    node->left = insert(node->left, product);
  } else if (product->id > node->product->id) {
    node->right = insert(node->right, product);
  } else // este modelo não aceita chaves duplicadas
    return node;

  // 2. Atualiza a altura do nó antecessor
  node->height = 1 + max(height(node->left), height(node->right));

  /* 3. pega o fator de balanceamento do antecessor
        para checar se este nó ficou desbalanceado */
  int balance = getBalance(node);

  // Analise dos quatro casos, árvore não

  // caso esquerda esquerda
  if (balance > 1 && product->id < node->left->product->id)
    return rightRotate(node);

  // Caso direita direita
  if (balance < -1 && product->id > node->right->product->id)
    return leftRotate(node);

  // caso esquerda direita
  if (balance > 1 && product->id > node->left->product->id) {
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }

  // caso direita esquerda
  if (balance < -1 && product->id < node->right->product->id) {
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }
  // retorna o ponteiro do nó inalterado
  return node;
}

Node *minValueNode(Node *node) {
  Node *current = node;
  /* loop para encontrar o nó mais a esquerda */
  while (current && current->left != NULL)
    current = current->left;
  return current;
}

Node *balanceTree(Node *root) {
  if (root == NULL)
    return root;
  root->height = 1 + max(height(root->left), height(root->right));
  int balance = getBalance(root);
  if (balance > 1 && getBalance(root->left) >= 0)
    return rightRotate(root);
  if (balance > 1 && getBalance(root->left) < 0) {
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }
  if (balance < -1 && getBalance(root->right) <= 0)
    return leftRotate(root);
  if (balance < -1 && getBalance(root->right) > 0) {
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }
}

// Função que apaga uma Chave da BST e retorna uma nova raiz
Node *deleteNode(Node *root, Product *product) {
  if (treeIsEmpty(root))
    return root;

  // testa se a chave buscada é menor que a raiz "atual"
  if (product->id < root->product->id) {
    root->left = deleteNode(root->left, product);
  }
  // testa se a chave buscada é maior que a "raiz"
  else if (product->id > root->product->id) {
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
    root->product->id = temp->product->id;
    // Apaga o sucessor em inorder
    root->right = deleteNode(root->right, temp->product);
  }

  // Verifica se vai precisar balancear, se precisar já faz!!
  balanceTree(root);
  return root;
}

//Verifica se a árvore está vazia
int treeIsEmpty(Node *root){
  return root == NULL;
}

// impressão da árvore e das alturas dos nós
void preOrder(Node *root) {
  if (!treeIsEmpty(root)) {
    printf("%d ", root->product->id);
    preOrder(root->left);
    preOrder(root->right);
  }
}

void printTree(Node *root, int desloc) {
  if (treeIsEmpty(root))
    return;
  printTree(root->right, desloc + 3);
  printf("%*s%d\n", desloc, "", root->product->id);
  printTree(root->left, desloc + 3);
}

void inOrder(Node *root) {
  if (!treeIsEmpty(root)) {
    inOrder(root->left);
    printf("\n%i", root->product->id);
    inOrder(root->right);
  }
}

void posOrder(Node *root) {
  if (!treeIsEmpty(root)) {
    posOrder(root->left);
    posOrder(root->right);
    printf("\n%i", root->product->id);
  }
}

int returnBiggestId(Node *root) {
  if (treeIsEmpty(root)) {
    return 0;
  }

  if (root->right != NULL) {
    return returnBiggestId(root->right);
  } else {
    return root->product->id;
  }
}

