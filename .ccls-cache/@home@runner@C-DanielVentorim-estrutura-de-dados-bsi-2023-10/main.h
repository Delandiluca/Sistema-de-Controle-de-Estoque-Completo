int max(int a, int b);
int height(Node *n);
Node *newNode(Product product);
Node *rightRotate(Node *y);
Node *leftRotate(Node *x);
int getBalance(Node *N);
Node *insert(Node *node, Product product);
void preOrder(Node *root);
void printTree(Node *root, int desloc);
void inOrder(Node *root);
void posOrder(Node *root);
Node *minValueNode(Node *node);
Node *deleteNode(Node *root, Product *product);
Node *balanceTree(Node *root);
int returnBiggestId(Node *root);
int treeIsEmpty(Node *root);
void createTree(Node **root);

void instructions();
void listSalesForProduct(Node* root, int idProduct);
void listProductsForMonth(Node* root, int month);
void listProducts(Node* root);
//void registerProduct(Node *root);
int generateId(Node *root);

