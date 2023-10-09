## Controle de estoque com dados armazenados em uma árvore AVL
<details>
<summary> Tabelas do sistema: </summary>
- Tabela com a identificação da empresa
	- CNPJ da empresa
  - Nome da empresa
  - Cidade da empresa

- Tabela de ítens
	- Id produto
  - Nome do produto
  - Custo do produto
  - Imposto ICMS do produto
  - Despesa operacional
  - Lucratividade
  - Preço de venda
  - Quantidade
- Tabela de Compras
	- Nota fiscal
  - Data da nota
  - Id do produto
  - Preço de custo
  - Imposto na nota de entrada
  - Quantidade
  - Valor
- Tabela de Vendas
	- Nota fiscal
  - Data da nota
  - Id do produto
  - Preço de venda
  - Imposto
  - Quantidade
  - Valor
</details>
<details>
<summary> Operações: </summary>
<details>
<summary> Cadastramento, alterações e exlusão de produtos: </summary>

- Calcular o preço de venda do produto
- PV = PC/(1 - MKP)
</details>

- Venda de produtos
- Compra de produtos
- Pesquisa de produtos
- Pesquisa de vendas
</details>
<details>
<summary> Relatórios no formato TXT: </summary>

- Relação de produtos em ordem alfabética com preço de compra preço de venda e saldo
- Relação de vendas do mês
- Extrato de movimentação de produtos
</details>

<details>
<summary> Modelo dos relatórios: </summary>

### Relação de produtos em ordem alfabética com preço de compra preço de venda e saldo
```
------------------------------------------------------
Empresa Terceiro SI
Relação de produtos
------------------------------------------------------
id Descrição Quantidade     Preço    Custo       Valor
------------------------------------------------------
 1 Impressora         50   1000.00   500.00   25000.00
 2 Monitor            10    500.00   250.00    2500.00
 3 TV 50"              5   2000.00  1500.00    7500.00
------------------------------------------------------
Valor em estoque                              35000.00
------------------------------------------------------
```
### Relação de vendas do mês
```
------------------------------------------
Empresa Terceiro SI
Relação de Vendas do mês 05
------------------------------------------
id Descrição Quantidade     Preço    Valor
------------------------------------------
 1 Impressora         1   1000.00  1000.00 
 2 Monitor            1    450.00   450.00
 3 TV 50"             1   2000.00  2000.00
 1 Impressora         1   1000.00  1000.00 
 3 TV 50"             1   2050.00  2050.00
 2 Monitor            1    500.00   500.00
------------------------------------------
Total                              7000.00
------------------------------------------
```
### Extrato de movimentação de produtos
```
------------------------------------------
Empresa Terceiro SI
Extrato de Vendas de MONITOR
------------------------------------------
id Data       Quantidade    Preço    Valor
------------------------------------------
 2 10/05/2023          1   450.00   450.00
 2 11/05/2023          1   500.00   500.00
------------------------------------------
Total                               950.00
------------------------------------------
```

</details>

<details>
<summary>Requisitos não funcionais </summary>

- As opções devem ficar disponíveis para o usuário em um menu;  
- Evite aumentar a complexidade do algoritmo implementado;
- Apenas as funções pedidas devem ser implementadas;
- Faça testes que garantam  que o programa não apresente inconsistências nem erros de runtime.
</details>

 
<details>
<summary>Pontuação da atividade </summary>

- Entrega do programa atendendo os requisitos funcionais e não funcionais – 5 pts;
- Clareza e legibilidade do código (comentários, nomes de variáveis, indentação.) - 2 pts;
- Controle de erros de runtime -  1pts;
- Apresentação da solução – 1pts;
- Correção das possíveis falhas encontradas no código  - 1pts.

</details>
 