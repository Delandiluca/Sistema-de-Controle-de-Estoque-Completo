#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void instructions() {
  printf("\n===================================================="
         "\n#         BEM VINDO AO CONTROLE DE ESTOQUE         #"
         "\n#                 DLTECHNOLOGY                     #"
         "\n====================================================\n"
         "# Escolha a opção desejada:\n\n"
         "#  1 Cadastrar Produto\n"
         "#  2 Alterar Produto\n"
         "#  3 Excluir Produto\n"
         "#  4 Registrar Venda\n"
         "#  5 Registrar Compra\n"
         "#  6 Buscar Produto\n"
         "#  7 Buscar Vendas\n"
         "#  8 Listar Relação de Produtos\n"
         "#  9 Listar Relação de Vendas por Mês\n"
         "#  10 Listar Extrato de Movimentação de Produto\n"
         "#  11 Sair...\n"
         "====================================================\n");
}

void listProducts(Node* root) {
    FILE *file = fopen("relatorio.txt", "w");
    if (file == NULL) {
        printf("\nErro ao abrir o arquivo!");
        return;
    }
    // Relatório de produtos
    fprintf(file, "------------------------------------------------------------\n");
    fprintf(file, "Empresa ...\n");
    fprintf(file, "Relação de produtos\n");
    fprintf(file, "------------------------------------------------------------\n");
    fprintf(file, "| id | Descrição | Quantidade  |  Preço  |  Custo  | Valor |\n");
    fprintf(file, "------------------------------------------------------------\n");
    //Aqui vai entrar função dos produtos em ordem alfabética!!
    fprintf(file, "------------------------------------------------------------\n");
    fprintf(file, "Total                                                      |\n");
    fprintf(file, "------------------------------------------------------------\n");
    fclose(file);
}

void listProductsForMonth(Node* root, int month) {
    FILE *file = fopen("relatorio.txt", "w");
    if (file == NULL) {
        printf("\nErro ao abrir o arquivo!");
        return;
    }
    // Relatório de produtos
    fprintf(file, "----------------------------------------------------\n");
    fprintf(file, "Empresa ...\n");
    fprintf(file, "Relação de Vendas do mês ...\n");
    fprintf(file, "----------------------------------------------------\n");
    fprintf(file, "| id | Descrição | Quantidade  |  Preço  |  Valor  |\n");
    fprintf(file, "----------------------------------------------------\n");
    //Aqui vai entrar as vendas do mês "month"
    fprintf(file, "----------------------------------------------------\n");
    fprintf(file, "Total                                              |\n");
    fprintf(file, "----------------------------------------------------\n");
    fclose(file);
}

void listSalesForProduct(Node* root, int idProduct){
  FILE *file = fopen("relatorio.txt", "w");
    if (file == NULL) {
        printf("\nErro ao abrir o arquivo!");
        return;
    }

    // Relatório de produtos
    fprintf(file, "----------------------------------------------------\n");
    fprintf(file, "Empresa ...\n");
    fprintf(file, "Relação de Vendas de ...\n");
    fprintf(file, "----------------------------------------------------\n");
    fprintf(file, "| id | Descrição | Quantidade  |  Preço  |  Valor  |\n");
    fprintf(file, "----------------------------------------------------\n");
    //Aqui vai entrar as vendas do produto "idProduct"
    fprintf(file, "----------------------------------------------------\n");
    fprintf(file, "Total                                              |\n");
    fprintf(file, "----------------------------------------------------\n");
    fclose(file);
}

//Gera um ID acima do último existente na árvore
int generateId(Node *root){
  return returnBiggestId(root) + 1;
}

void registerProduct(Node *root){
  //Inicializa a estrutura de produto e preenche com os dados fornecidos pelo user
  Product product;
  product.id = generateId(root); //seta o id automático
  printf("\nDigite o nome do Produto: ");
  scanf("%s", product.name);
  printf("\nDigite o Valor de Custo do Produto: ");
  scanf("%f", &product.cost);
  printf("\nDigite o imposto ICMS do produto: ");
  scanf("%f", &product.tax);
  printf("\nDigite a despesa operacional do produto: ");
  scanf("%f", &product.expenseOperational);
  printf("\nDigite a lucratividade do produto: ");
  scanf("%f", &product.lucrativity);
  printf("\nDigite o preço de venda do produto: ");
  scanf("%f", &product.priceSale);
  printf("\nDigite a quantidade do produto: ");
  scanf("%d", &product.quantity);

  printf("\n%d", product.id);
  printf("\n%s", product.name);
  printf("\n%f", product.cost);
  printf("\n%f", product.tax);
  printf("\n%f", product.expenseOperational);
  printf("\n%f", product.lucrativity);
  printf("\n%f", product.priceSale);
  printf("\n%d", product.quantity);

  //Insere o novo produto na árvore avl
  insert(root, &product);

  inOrder(root);
  puts("\n");
  printTree(root, 0);
}

