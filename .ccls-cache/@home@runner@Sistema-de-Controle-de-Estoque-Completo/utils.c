#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Gera um ID acima do último existente na árvore
int generateId(Node *root) { return returnBiggestId(root) + 1; }

// Gerar UUID random para notinha fiscal
int generateIdInvoice(FILE *file, char type) {
  fseek(file, 0, SEEK_END);
  if (ftell(file) <= 0) {
    return 0;
  } else if (type == 'P') {
    Purchase purchase;
    fseek(file, -sizeof(Purchase),
          SEEK_END); // posiciona o ponteiro no último registro
    fread(&purchase, sizeof(Purchase), 1, file); // lê o último registro
    return purchase.invoice;
  } else {
    Sale sale;
    fseek(file, -sizeof(Sale),
          SEEK_END); // posiciona o ponteiro no último registro
    fread(&sale, sizeof(Sale), 1, file); // lê o último registro
    return sale.invoice;
  }
}

double calculateCostProduct(Product product) {
  FILE *fPtr;
  fPtr = fopen("purchases.dat", "rb+");

  if (fPtr == NULL) {
    puts("\nErro ao Abrir o Arquivo..");
    return 0;
  }

  double sum = 0;
  int count = 0;
  double midCostPrice;
  fseek(fPtr, 0, SEEK_SET);
  Purchase purchase;
  while (fread(&purchase, sizeof(Purchase), 1, fPtr) == 1) {
    if (purchase.idProduct == product.id) {
      sum += purchase.costPrice;
      count += 1;
    }
  }
  fclose(fPtr);

  return midCostPrice = sum / count;
}

double calculatePriceSaleProduct(Product product) {
  //return product.cost + (((product.lucrativity + product.expenseOperational + product.tax) / 100) * product.cost); 
  return product.cost / (1 - ((product.expenseOperational + product.lucrativity + product.tax) / 100));
}

// Função para cadastrar um novo produto
void registerProduct(Node **root) {
  Product product;

  product.id = generateId(*root);
  printf("Digite o Nome do produto: ");
  scanf(" %[^\n]s", product.name);
  product.cost = 0;
  printf("Digite o Imposto ICMS do produto (%%): ");
  scanf("%f", &(product.tax));
  printf("Digite a Despesa operacional do produto (%%): ");
  scanf("%f", &(product.expenseOperational));
  printf("Digite a Lucratividade do produto (%%): ");
  scanf("%f", &(product.lucrativity));
  product.quantity = 0;

  // Calculo do Preço de Venda
  product.priceSale = 0;

  *root = insert(*root, product);
  saveArchive(*root);
}

// Deletar um produto da árvore
void deleteProduct(Node **root, int id) {
  Node *no = searchForId(*root, id);
  Product product = no->product;
  *root = deleteNode(*root, product);
  saveArchive(*root);
  deletePurchaseForProduct(product);
  deleteSaleForProduct(product);
}

void deletePurchaseForProduct(Product product) {
  const char *nameFileOrigin = "purchases.dat";
  const char *nameFileTemp = "temp_purchases.dat";

  FILE *fileOrigin = fopen(nameFileOrigin, "rb");
  if (fileOrigin == NULL) {
    printf("\nErro ao abrir o arquivo original.\n");
    return;
  }

  FILE *fileTemp = fopen(nameFileTemp, "wb");
  if (fileTemp == NULL) {
    printf("\nErro ao criar o arquivo temporário.\n");
    fclose(fileOrigin);
    return;
  }

  fseek(fileOrigin, 0, SEEK_SET);
  Purchase purchase;
  while (fread(&purchase, sizeof(Purchase), 1, fileOrigin)) {
    if (purchase.idProduct != product.id) {
      fwrite(&purchase, sizeof(Purchase), 1, fileTemp);
    }
  }

  fclose(fileOrigin);
  fclose(fileTemp);

  if (remove(nameFileOrigin) != 0) {
    printf("\nErro ao remover o arquivo original.\n");
    return;
  }

  if (rename(nameFileTemp, nameFileOrigin) != 0) {
    printf("\nErro ao renomear o arquivo temporário.\n");
    return;
  }

  printf("\nRegistro de Compras do Produto Removido Com Sucesso.\n");
}

void deleteSaleForProduct(Product product) {
  const char *nameFileOrigin = "sales.dat";
  const char *nameFileTemp = "temp_sales.dat";

  FILE *fileOrigin = fopen(nameFileOrigin, "rb");
  if (fileOrigin == NULL) {
    printf("\nErro ao abrir o arquivo original.\n");
    return;
  }

  FILE *fileTemp = fopen(nameFileTemp, "wb");
  if (fileTemp == NULL) {
    printf("\nErro ao criar o arquivo temporário.\n");
    fclose(fileOrigin);
    return;
  }

  fseek(fileOrigin, 0, SEEK_SET);
  Sale sale;
  while (fread(&sale, sizeof(Sale), 1, fileOrigin)) {
    if (sale.idProduct != product.id) {
      fwrite(&sale, sizeof(Sale), 1, fileTemp);
    }
  }

  fclose(fileOrigin);
  fclose(fileTemp);

  if (remove(nameFileOrigin) != 0) {
    printf("\nErro ao remover o arquivo original.\n");
    return;
  }

  if (rename(nameFileTemp, nameFileOrigin) != 0) {
    printf("\nErro ao renomear o arquivo temporário.\n");
    return;
  }

  printf("\nRegistro de Vendas do Produto Removido Com Sucesso.\n");
}

// Editar produto direto da árvore
void editProduct(Node *root, int productId) {
  Node *productNode = searchForId(root, productId);

  if (productNode == NULL) {
    printf("\nProduto com ID %d não encontrado.\n", productId);
    return;
  }

  printf("\nNome Atual: %s", productNode->product.name);
  puts("\nDigite o novo nome para o produto: ");
  scanf(" %[^\n]s", productNode->product.name);

  // printf("\nCusto Atual: R$%.2f", root->product.cost);
  // puts("\nDigite o novo preço de custo para o produto: ");
  // scanf("%f", &root->product.cost);

  printf("\nICMS Atual: %.2f%%", productNode->product.tax);
  puts("\nDigite o novo ICMS para o produto: ");
  scanf("%f", &productNode->product.tax);

  printf("\nDespesa Operacional Atual: %.2f%%",
         productNode->product.expenseOperational);
  puts("\nDigite o novo valor de despesa operacional para o produto: ");
  scanf("%f", &productNode->product.expenseOperational);

  printf("\nLucratividade Atual: %.2f%%", productNode->product.lucrativity);
  puts("\nDigite a nova lucratividade do produto: ");
  scanf("%f", &productNode->product.lucrativity);

  printf("\nPreço de Venda Atual: R$%.2f", productNode->product.priceSale);
  // Calculo do Preço de Venda
  // productNode->product.priceSale = productNode->product.cost / (1 -
  // (productNode->product.tax + productNode->product.expenseOperational) /
  // 100);
  printf("\nNovo Preço de Venda: R$%.2f", productNode->product.priceSale);

  // printf("\nQuantidade Atual: %d", root->product.quantity);
  // puts("\nDigite a nova quantidade do produto: ");
  // scanf("%d", &root->product.quantity);

  saveArchive(root);
  productNode->product.cost = calculateCostProduct(productNode->product);
  productNode->product.priceSale = calculatePriceSaleProduct(productNode->product);
  puts("\nProduto Alterado com Sucesso!!\n");
}

// Printar as informações de um produto especifico
void searchProduct(Node *root, int productId) {
  FILE *fPtr;
  fPtr = fopen("painel.txt", "w");

  if (fPtr == NULL) {
    puts("\nErro ao Abrir o Arquivo...\n");
    return;
  }

  Node *node = searchForId(root, productId);
  Product product = node->product;

  fprintf(fPtr, "----------------------------------------------\n");
  fprintf(fPtr, "| Empresa DLTECHNOLOGY                       |\n");
  fprintf(fPtr, "| Detalhes de %s\n", product.name);
  fprintf(fPtr, "----------------------------------------------\n");
  fprintf(fPtr, "| ID: %d", product.id);
  fprintf(fPtr, "\n| Nome: %s", product.name);
  fprintf(fPtr, "\n| Custo do Produto: R$%.2f", product.cost);
  fprintf(fPtr, "\n| Imposto ICMS: %.2f%%", product.tax);
  fprintf(fPtr, "\n| Despesa Operacional: %.2f%%", product.expenseOperational);
  fprintf(fPtr, "\n| Lucratividade: %.2f%%", product.lucrativity);
  fprintf(fPtr, "\n| Preço de Venda: R$%.2f", product.priceSale);
  fprintf(fPtr, "\n| Quantidade: %d\n", product.quantity);
  fprintf(fPtr, "----------------------------------------------\n");

  fclose(fPtr);
}

void searchSale(int invoice){
  FILE *fPtr;
  FILE* file;
  file = fopen("sales.dat", "rb");
  fPtr = fopen("painel.txt", "w");
  
  if (file == NULL) {
    puts("\nErro ao Abrir o Arquivo Binario...\n");
    return;
  } else if (fPtr == NULL) {
    puts("\nErro ao Abrir o Arquivo TXT...\n");
    return;
  }

  Sale sale;
  fseek(file, 0, SEEK_SET);
  while (fread(&sale, sizeof(Sale), 1, file) == 1) {
    if (sale.invoice == invoice) {
      fprintf(fPtr, "----------------------------------------------\n");
      fprintf(fPtr, "| Empresa DLTECHNOLOGY                       |\n");
      fprintf(fPtr, "| Detalhes de Venda da Nota Fiscal %d\n", invoice);
      fprintf(fPtr, "----------------------------------------------\n");
      fprintf(fPtr, "| Nota Fiscal: %d", sale.invoice);
      fprintf(fPtr, "\n| Data: %s", sale.date);
      fprintf(fPtr, "\n| ID do Produto: %d", sale.idProduct);
      fprintf(fPtr, "\n| Preço de Venda: R$%.2lf", sale.priceSale);
      fprintf(fPtr, "\n| Imposto: %.2f%%", sale.tax);
      fprintf(fPtr, "\n| Quantidade: %d", sale.quantity);
      fprintf(fPtr, "\n| Valor: R$%.2f", sale.value);
      fprintf(fPtr, "\n----------------------------------------------\n");
    }
  }

  fclose(fPtr);
  fclose(file);
}

// Salvar toda a árvore AVL no arquivo
void saveArchive(Node *root) {
  FILE *fp;
  fp = fopen("products.dat", "wb");
  if (fp == NULL) {
    puts("\nErro ao abrir o arquivo!!\n");
    return;
  }
  saveNode(fp, root);
  fclose(fp);
}

// Salvar cada Nó no arquivo em pre order
void saveNode(FILE *fp, Node *node) {
  if (node == NULL) {
    return;
  }
  fwrite(&(node->product), sizeof(Product), 1, fp);
  saveNode(fp, node->left);
  saveNode(fp, node->right);
}

// Carregar produtos do arquivo e inserir por id
Node *loadArchive() {
  FILE *fp;
  fp = fopen("products.dat", "rb+");
  if (fp == NULL) {
    printf("\nErro ao abrir o arquivo!\n");
    return NULL;
  }
  Node *root = NULL;
  Product product;
  while (fread(&product, sizeof(Product), 1, fp)) {
    root = insert(root, product);
  }
  fclose(fp);
  return root;
}

// Carregar produtos do arquivo e inserir em ordem alfabetica
Node *loadArchiveInOrder() {
  FILE *fp;
  fp = fopen("products.dat", "rb+");
  if (fp == NULL) {
    printf("\nErro ao abrir o arquivo!\n");
    return NULL;
  }
  Node *root = NULL;
  Product product;
  while (fread(&product, sizeof(Product), 1, fp)) {
    root = insertOrderName(root, product);
  }
  fclose(fp);
  return root;
}

// Registrar uma Compra
void registerPurchase(Node *root) {
  FILE *fPtr;
  fPtr = fopen("purchases.dat", "ab+");

  if (fPtr == NULL) {
    puts("\nErro ao Abrir o Arquivo...\n");
    return;
  }

  Purchase purchase;
  purchase.invoice = generateIdInvoice(fPtr, 'P') + 1;

  puts("\nDigite o ID do produto que deseja comprar: ");
  scanf(" %d", &purchase.idProduct);

  Node *productNode = searchForId(root, purchase.idProduct);
  // printf("\n%d %d %s", purchase.invoice, product.id, product.name); - DEBUG
  puts("\nDigite a Data a constar na Nota Fiscal (dd/mm/aa): ");
  scanf("%s", purchase.date);
  puts("\nDigite o preço de custo do produto: ");
  scanf("%f", &purchase.costPrice);

  purchase.tax = productNode->product.tax;

  puts("\nDigite a quantidade comprada deste produto: ");
  scanf("%d", &purchase.quantity);

  // Atualiza a quantidade do produto em estoque
  productNode->product.quantity += purchase.quantity;
  printf("%d %d", productNode->product.quantity, purchase.quantity);

  purchase.value = purchase.costPrice * purchase.quantity;

  // fseek(fPtr, (purchase.invoice - 1) * sizeof(Purchase), SEEK_SET);
  fwrite(&purchase, sizeof(Purchase), 1, fPtr);

  fclose(fPtr);

  productNode->product.cost = calculateCostProduct(productNode->product);
  productNode->product.priceSale =
      calculatePriceSaleProduct(productNode->product);
  printf("\n%.2lf %.2lf", productNode->product.priceSale,
         productNode->product.cost);
  printf("\n%.2lf", calculatePriceSaleProduct(productNode->product));
  puts("\nCompra Registrada Com Sucesso!!\n");
  saveArchive(root);
}

// Listar todas as Compras
void listPurchases() {
  FILE *fPtr;
  fPtr = fopen("purchases.dat", "rb+");

  if (fPtr == NULL) {
    puts("\nErro ao Abrir o Arquivo...\n");
    return;
  }

  fseek(fPtr, 0, SEEK_SET);
  Purchase purchase;
  while (fread(&purchase, sizeof(Purchase), 1, fPtr) == 1) {
    printf("\n%d %s %d %d %.2lf %.2lf", purchase.invoice, purchase.date,
           purchase.idProduct, purchase.quantity, purchase.tax, purchase.value);
  }

  fclose(fPtr);
}

// Listar todas as compras de um determinado produto
void listPurchasesForProduct(FILE *file, Product product, double *totalSum) {
  FILE *fPtr;
  fPtr = fopen("purchases.dat", "rb+");

  if (fPtr == NULL) {
    puts("\nErro ao Abrir o Arquivo...\n");
    return;
  }

  fseek(fPtr, 0, SEEK_SET);
  Purchase purchase;
  while (fread(&purchase, sizeof(Purchase), 1, fPtr) == 1) {
    if (purchase.idProduct == product.id) {
      fprintf(file, "    %-5d%-22s%-12sR$%-13.2lf%-8dR$%.2lf\n",
              purchase.invoice, product.name, purchase.date, purchase.costPrice,
              purchase.quantity, purchase.value);
      *totalSum += purchase.value;
    }
  }

  fclose(fPtr);
}

void registerSale(Node *root) {
  FILE *fPtr;
  fPtr = fopen("sales.dat", "ab+");

  if (fPtr == NULL) {
    puts("\nErro ao Abrir o Arquivo...\n");
    return;
  }

  Sale sale;
  sale.invoice = generateIdInvoice(fPtr, 'S') + 1;

  puts("\nDigite o ID do produto que deseja vender: ");
  scanf(" %d", &sale.idProduct);

  Node *productNode = searchForId(root, sale.idProduct);
  // printf("\n%d %d %s", purchase.invoice, product.id, product.name); - DEBUG

  puts("\nDigite a Data a constar na Nota Fiscal (dd/mm/aa): ");
  scanf("%s", sale.date);

  sale.priceSale = productNode->product.priceSale;
  sale.tax = productNode->product.tax;

  puts("\nDigite a quantidade vendida deste produto: ");
  scanf("%d", &sale.quantity);

  // Tratamento de possível erro
  if (productNode->product.quantity < sale.quantity) {
    puts("\nQuantidade insuficiente em estoque para venda...\n");
    return;
  }

  sale.value = sale.priceSale * sale.quantity;

  // Atualiza a quantidade do produto no estoque
  productNode->product.quantity -= sale.quantity;

  fwrite(&sale, sizeof(Sale), 1, fPtr);

  fclose(fPtr);

  productNode->product.cost = calculateCostProduct(productNode->product);
  productNode->product.priceSale =
      calculatePriceSaleProduct(productNode->product);
  puts("\nVenda Registrada Com Sucesso!!\n");
  saveArchive(root);
}

// Listar todas as Vendas
void listSales() {
  FILE *fPtr;
  fPtr = fopen("sales.dat", "rb+");

  if (fPtr == NULL) {
    puts("\nErro ao Abrir o Arquivo...\n");
    return;
  }

  fseek(fPtr, 0, SEEK_SET);
  Sale sale;
  while (fread(&sale, sizeof(Sale), 1, fPtr) == 1) {
    printf("\n%d %s %d %d %.2lf %.2lf", sale.invoice, sale.date, sale.idProduct,
           sale.quantity, sale.tax, sale.value);
  }

  fclose(fPtr);
}

void listSalesForProduct(FILE *file, Product product, double *totalSum) {
  FILE *fPtr;
  fPtr = fopen("sales.dat", "rb+");

  if (fPtr == NULL) {
    puts("\nErro ao Abrir o Arquivo...\n");
    return;
  }

  fseek(fPtr, 0, SEEK_SET);
  Sale sale;
  while (fread(&sale, sizeof(Sale), 1, fPtr) == 1) {
    if (sale.idProduct == product.id) {
      fprintf(file, "    %-5d%-22s%-12sR$%-13.2lf%-8dR$%.2lf\n", sale.invoice,
              product.name, sale.date, product.cost, sale.quantity, sale.value);
      *totalSum += sale.value;
    }
  }

  fclose(fPtr);
}

void listSalesForMonth(FILE *file, char *targetMonth, double *totalSum, Node* root) {
  FILE *fPtr;
  fPtr = fopen("sales.dat", "rb+");

  if (fPtr == NULL) {
    puts("\nErro ao Abrir o Arquivo...\n");
    return;
  }

  fseek(fPtr, 0, SEEK_SET);
  Sale sale;
  while (fread(&sale, sizeof(Sale), 1, fPtr) == 1) {
    int saleMonth;
    if (sscanf(sale.date, "%*d/%d/%*d", &saleMonth) != 1) {
      puts("\nErro ao extrair o mês da data.\n");
      fclose(fPtr);
      return;
    }

    if (saleMonth == atoi(targetMonth)) {
      Product product = searchForId(root, sale.idProduct)->product;
      fprintf(file, "   %-5d%-22s%-12sR$%-13.2lf%-8dR$%.2lf\n", sale.invoice, product.name, sale.date, product.cost, sale.quantity, sale.value);
      *totalSum += sale.value;
    }
  }

  fclose(fPtr);
}



void listProductsForMonth(Node *root, char *month) {
  FILE *file = fopen("painel.txt", "w");
  if (file == NULL) {
    printf("\nErro ao abrir o arquivo!");
    return;
  }
  double totalSalesSum = 0;
  // Relatório de produtos
  fprintf(file, "---------------------------------------------------------------------------\n");
  fprintf(file, "| Empresa DLTECHNOLOGY                                                    |\n");
  fprintf(file, "| Relação de Vendas do mês %s\n", month);
  fprintf(file, "---------------------------------------------------------------------------\n");
  fprintf(file, "| Nota |         Nome         |   Data   |  Custo  | Quantidade |  Total  |\n");
  fprintf(file, "---------------------------------------------------------------------------\n");
  listSalesForMonth(file, month, &totalSalesSum, root);
  fprintf(file, "---------------------------------------------------------------------------\n");
  fprintf(file, "| Total:                                                        R$%.2lf|\n", totalSalesSum);
  fprintf(file, "------------------------------------------------------------------------------\n");
  fclose(file);
}

void listMovimentationsForProduct(Node *root, int idProduct) {
  FILE *file = fopen("painel.txt", "w");
  if (file == NULL) {
    printf("\nErro ao abrir o arquivo!");
    return;
  }

  Node *no = searchForId(root, idProduct);
  if (no == NULL) {
    puts("\nERRO: Produto não Encontrado no Sistema!!\n");
    return;
  }
  Product product = no->product;
  // Product product = searchForId(root, idProduct)->product;
  double totalPurchaseSum = 0;
  double totalSalesSum = 0;
  // Relatório de produtos
  fprintf(file, "--------------------------------------------------------------"
                "-------------\n");
  fprintf(file, "| Empresa DLTECHNOLOGY                                        "
                "            |\n");
  fprintf(file, "| Extrato de Movimentações de %s\n", product.name);
  fprintf(file, "--------------------------------------------------------------"
                "-------------\n");
  fprintf(file, "| Nota |         Nome         |   Data   |  Custo  | "
                "Quantidade |  Total  |\n");
  fprintf(file, "--------------------------------------------------------------"
                "-------------\n");
  fprintf(file, "| Compras:                                                    "
                "            |\n");
  fprintf(file, "--------------------------------------------------------------"
                "-------------\n");
  listPurchasesForProduct(file, product, &totalPurchaseSum);
  fprintf(file, "--------------------------------------------------------------"
                "-------------\n");
  fprintf(file, "| Vendas:                                                     "
                "            |\n");
  fprintf(file, "--------------------------------------------------------------"
                "-------------\n");
  listSalesForProduct(file, product, &totalSalesSum);
  fprintf(file, "--------------------------------------------------------------"
                "-------------\n");
  fprintf(file, "| Saldo: R$%.3lf\n", totalSalesSum - totalPurchaseSum);
  fprintf(file, "--------------------------------------------------------------"
                "-------------\n");
  fclose(file);
}

void listProducts(Node *root) {
  FILE *file = fopen("painel.txt", "w");
  if (file == NULL) {
    printf("\nErro ao abrir o arquivo!");
    return;
  }
  double total = 0;
  // Relatório de produtos
  fprintf(file, "--------------------------------------------------------------"
                "--------\n");
  fprintf(file, "| Empresa DLTECHNOLOGY                                        "
                "       |\n");
  fprintf(file, "| Relação de Produtos                                         "
                "       |\n");
  fprintf(file, "--------------------------------------------------------------"
                "--------\n");
  fprintf(file, "| ID |  Nome do Produto  | Quantidade  |  Preço  |  Custo  |  "
                "Total  |\n");
  fprintf(file, "--------------------------------------------------------------"
                "--------\n");
  printTreeToFile(root, file, &total);
  fprintf(file, "--------------------------------------------------------------"
                "--------\n");
  fprintf(file, "| Total: R$%56.2lf  |\n", total);
  fprintf(file, "--------------------------------------------------------------"
                "--------\n");
  fclose(file);
}

void instructions() {
  printf("\n===================================================="
         "\n#         BEM VINDO AO CONTROLE DE ESTOQUE         #"
         "\n#                 DLTECHNOLOGY                     #"
         "\n====================================================\n"
         "#           Escolha a opção desejada:              #\n"
         "----------------------------------------------------\n"
         "# * 1 Cadastrar Produto                            #\n"
         "# - 2 Alterar Produto                              #\n"
         "# * 3 Excluir Produto                              #\n"
         "# - 4 Registrar Venda                              #\n"
         "# * 5 Registrar Compra                             #\n"
         "# - 6 Buscar Produto                               #\n"
         "# * 7 Buscar Vendas                                #\n"
         "# - 8 Listar Relação de Produtos                   #\n"
         "# * 9 Listar Relação de Vendas por Mês             #\n"
         "# - 10 Listar Extrato de Movimentação de Produto   #\n"
         "# * 11 Sair...                                     #\n"
         "====================================================\n");
}
