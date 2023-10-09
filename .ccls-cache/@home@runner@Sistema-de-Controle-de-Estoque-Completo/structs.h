typedef struct Product {
  int id;
  char name[30];
  float cost;
  float tax;
  float expenseOperational;
  float lucrativity;
  float priceSale;
  int quantity;
} Product;

typedef struct Purchase {
  int invoice;
  char date[30];
  int idProduct;
  float costPrice;
  float tax;
  int quantity;
  float value;
} Purchase;

typedef struct Sale {
  int invoice;
  char date[30];
  int idProduct;
  float priceSale;
  float tax;
  int quantity;
  float value;
} Sale;

typedef struct Company {
  char cnpj[14];
  char name[50];
  char city[30];
} Company;

typedef struct Client{
  char name[30];
  char city[30];
  char cpf[11];
} Client;


typedef struct Invoice{
  int code;
  
} Invoice;

typedef struct Node {
  Product product;
  struct Node* left;
  struct Node* right;
  int height;
} Node;