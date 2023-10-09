#include "treeBinary.h"
#include <stdio.h>

// Textos De Interação c/ Usuário
void instructions();
void listMovimentationsForProduct(Node *root, int idProduct);
void listProductsForMonth(Node *root, char *month);
void listProducts(Node *root);

// Utilitários
int generateId(Node *root);
int generateIdInvoice(FILE *file, char type);

// Arquivos
void saveNode(FILE *fp, Node *node);
void saveArchive(Node *root);
Node *loadArchive();
Node *loadArchiveInOrder();

// Operações
void registerProduct(Node **root);
void deleteProduct(Node **root, int id);
void editProduct(Node *root, int productId);
void searchProduct(Node *root, int productId);

void registerPurchase(Node *root);
void listPurchases();
void listPurchasesForProduct(FILE *file, Product product, double *totalSum);
void listSalesForProduct(FILE *file, Product product, double *totalSum);
void registerSale(Node *root);
void listSales();
void listSalesForMonth(FILE* file, char *targetMonth, double* totalSum, Node* root);

double calculateCostProduct(Product product);
double calculatePriceSaleProduct(Product product);

void deletePurchaseForProduct(Product product);
void deleteSaleForProduct(Product product);

void searchSale(int invoice);