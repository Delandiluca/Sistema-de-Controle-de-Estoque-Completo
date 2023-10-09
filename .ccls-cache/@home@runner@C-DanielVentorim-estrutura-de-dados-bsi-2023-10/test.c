#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura do Produto
typedef struct {
  int id;
  char nome[50];
  float custo;
  float icms;
  float despesaOperacional;
  float lucratividade;
  float precoVenda;
  int quantidade;
} Produto;

// Definição do nó da árvore AVL
typedef struct No {
  Produto produto;
  struct No *esquerda;
  struct No *direita;
  int altura;
} No;

// Função para calcular a altura de um nó
int altura(No *no) {
  if (no == NULL)
    return 0;
  return no->altura;
}

// Função para calcular o máximo entre dois números
int max(int a, int b) { return (a > b) ? a : b; }

// Função para criar um novo nó da árvore AVL
No *novoNo(Produto produto) {
  No *no = (No *)malloc(sizeof(No));
  no->produto = produto;
  no->esquerda = NULL;
  no->direita = NULL;
  no->altura = 1;
  return no;
}

// Função para realizar uma rotação simples à direita
No *rotacaoDireita(No *y) {
  No *x = y->esquerda;
  No *T2 = x->direita;

  x->direita = y;
  y->esquerda = T2;

  y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;
  x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;

  return x;
}

// Função para realizar uma rotação simples à esquerda
No *rotacaoEsquerda(No *x) {
  No *y = x->direita;
  No *T2 = y->esquerda;

  y->esquerda = x;
  x->direita = T2;

  x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;
  y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;

  return y;
}

// Função para obter o fator de balanceamento de um nó
int fatorBalanceamento(No *no) {
  if (no == NULL)
    return 0;
  return altura(no->esquerda) - altura(no->direita);
}

// Função para inserir um produto na árvore AVL
No *inserir(No *no, Produto produto) {
  if (no == NULL)
    return novoNo(produto);

  if (produto.id < no->produto.id)
    no->esquerda = inserir(no->esquerda, produto);
  else if (produto.id > no->produto.id)
    no->direita = inserir(no->direita, produto);
  else
    return no;

  no->altura = 1 + max(altura(no->esquerda), altura(no->direita));

  int balanceamento = fatorBalanceamento(no);

  // Casos de rotação
  if (balanceamento > 1 && produto.id < no->esquerda->produto.id)
    return rotacaoDireita(no);

  if (balanceamento < -1 && produto.id > no->direita->produto.id)
    return rotacaoEsquerda(no);

  if (balanceamento > 1 && produto.id > no->esquerda->produto.id) {
    no->esquerda = rotacaoEsquerda(no->esquerda);
    return rotacaoDireita(no);
  }

  if (balanceamento < -1 && produto.id < no->direita->produto.id) {
    no->direita = rotacaoDireita(no->direita);
    return rotacaoEsquerda(no);
  }

  return no;
}

// Função para buscar um produto por Id na árvore AVL
No *buscarPorId(No *no, int id) {
  if (no == NULL || no->produto.id == id)
    return no;

  if (id < no->produto.id)
    return buscarPorId(no->esquerda, id);

  return buscarPorId(no->direita, id);
}

// Função para listar todos os produtos em ordem crescente de Id
void listarProdutos(No *no) {
  if (no != NULL) {
    listarProdutos(no->esquerda);
    printf("Id: %d, Nome: %s, Preco de Venda: %.2f\n", no->produto.id,
           no->produto.nome, no->produto.precoVenda);
    listarProdutos(no->direita);
  }
}

// Função para salvar a árvore AVL em um arquivo binário
void salvarArvoreEmArquivo(No *no, FILE *arquivo) {
  if (no != NULL) {
    salvarArvoreEmArquivo(no->esquerda, arquivo);
    fwrite(&(no->produto), sizeof(Produto), 1, arquivo);
    salvarArvoreEmArquivo(no->direita, arquivo);
  }
}

// Função para carregar a árvore AVL a partir de um arquivo binário
No *carregarArvoreDeArquivo(FILE *arquivo) {
  No *raiz = NULL;
  Produto produto;

  while (fread(&produto, sizeof(Produto), 1, arquivo) == 1) {
    raiz = inserir(raiz, produto);
  }

  return raiz;
}

// Função para cadastrar um novo produto
void cadastrarProduto(No **raiz) {
  Produto produto;

  printf("Digite o Id do produto: ");
  scanf("%d", &(produto.id));
  printf("Digite o Nome do produto: ");
  scanf(" %[^\n]s", produto.nome);
  printf("Digite o Custo do produto: ");
  scanf("%f", &(produto.custo));
  printf("Digite o Imposto ICMS do produto: ");
  scanf("%f", &(produto.icms));
  printf("Digite a Despesa operacional do produto: ");
  scanf("%f", &(produto.despesaOperacional));
  printf("Digite a Lucratividade do produto: ");
  scanf("%f", &(produto.lucratividade));
  printf("Digite a Quantidade do produto: ");
  scanf("%d", &(produto.quantidade));

  produto.precoVenda = produto.custo + produto.icms +
                       produto.despesaOperacional + produto.lucratividade;

  *raiz = inserir(*raiz, produto);
}

int main() {
  No *raiz = NULL;
  FILE *arquivo = fopen("produtos.bin", "rb");

  if (arquivo != NULL) {
    raiz = carregarArvoreDeArquivo(arquivo);
    fclose(arquivo);
  }

  int opcao;
  do {
    printf("\nEscolha uma opcao:\n");
    printf("1. Cadastrar produto\n");
    printf("2. Listar produtos\n");
    printf("3. Pesquisar produto por Id\n");
    printf("4. Sair\n");
    scanf("%d", &opcao);

    switch (opcao) {
    case 1:
      cadastrarProduto(&raiz);
      break;
    case 2:
      listarProdutos(raiz);
      break;
    case 3: {
      int id;
      printf("Digite o Id do produto: ");
      scanf("%d", &id);
      No *resultado = buscarPorId(raiz, id);
      if (resultado != NULL) {
        printf("Produto encontrado:\n");
        printf("Id: %d, Nome: %s, Preco de Venda: %.2f\n",
               resultado->produto.id, resultado->produto.nome,
               resultado->produto.precoVenda);
      } else {
        printf("Produto nao encontrado.\n");
      }
      break;
    }
    case 4:
      arquivo = fopen("produtos.bin", "wb");
      if (arquivo != NULL) {
        salvarArvoreEmArquivo(raiz, arquivo);
        fclose(arquivo);
      }
      break;
    default:
      printf("Opcao invalida. Tente novamente.\n");
      break;
    }
  } while (opcao != 4);

  return 0;
}
