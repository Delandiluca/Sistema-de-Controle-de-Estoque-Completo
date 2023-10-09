#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {

  // Lendo as informações de "Products.dat" e guardando na árvore...
  Node *treeProduct = loadArchive();
  Node *treeOrderProduct = loadArchiveInOrder();

  unsigned int choice;
  unsigned int productId;
  unsigned char month[3];

  instructions();
  printf("%s", "? ");
  scanf("%u", &choice);

  while (choice != 11) {
    switch (choice) {

    case 1:
      registerProduct(&treeProduct);
      puts("\nProduto cadastrado no sistema com sucesso!!");
      break;
    case 2:
      puts("\nDigite o ID do produto que deseja editar: ");
      scanf("%d", &productId);
      editProduct(treeProduct, productId);
      break;
    case 3:
      puts("\nDigite o ID do produto que deseja excluir do estoque..: ");
      scanf("%d", &productId);
      deleteProduct(&treeProduct, productId);
      puts("\nProduto removido com sucesso do estoque!!\n");
      break;
    case 4:
      // Registrar Venda
      registerSale(treeProduct);
      break;
    case 5:
      registerPurchase(treeProduct);
      break;
    case 6:
      puts("\nDigite o ID do produto que deseja visualizar: ");
      scanf("%d", &productId);
      searchProduct(treeProduct, productId);
      break;
    case 7:
      // Buscar Vendas
      puts("\nDigite a Nota Fiscal de venda que deseja visualizar: ");
      scanf("%d", &productId);
      searchSale(productId);
      break;
    case 8:
      saveArchive(treeProduct); //De Segurança...
      treeOrderProduct = loadArchiveInOrder();
      listProducts(treeOrderProduct);
      printTree(treeProduct, 0);
      //printTreeOrder(treeOrderProduct, 0);
      //inOrderTree(treeOrderProduct);
      break;
    case 9:
      puts("\nDigite o mês deseja visualizar as vendas (1-12): ");
      scanf("%2s", month);
      listProductsForMonth(treeProduct, month);
      break;
    case 10:
      // Extrato de Vendas por Produto
      puts("\nDigite o ID do produto que deseja buscar: ");
      scanf("%d", &productId);
      listMovimentationsForProduct(treeProduct, productId);
      break;
    default:
      puts("\nOpção Inválida.\n");
      instructions();
      break;
    }
    instructions();
    printf("%s", "? ");
    scanf("%u", &choice);
  }
  //saveArchive(treeProduct);
  puts("\n\nObrigado por utilizar nosso Sistema. Até Logo!!\n\n");
  return 0;
}
