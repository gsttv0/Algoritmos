# Sistema de Gestão de Vendas e Estoque 🛒

Aplicação em C++ desenvolvida para a disciplina de Algoritmos e Estrutura de Dados. O sistema simula um PDV (Ponto de Venda), gerenciando simultaneamente o estoque de produtos e o histórico financeiro de vendas utilizando estruturas de dados compostas (`structs`).

## 🚀 Funcionalidades

* **Controle de Estoque:** Inclusão de produtos com validação de nome e código único.
* **Sistema de Vendas:**
    * Baixa automática no estoque ao realizar uma venda.
    * Verificação de disponibilidade de quantidade.
    * Registro financeiro separado (Relatório de Vendas).
* **Relatórios Gerenciais:**
    * Listagem de produtos em estoque.
    * Listagem detalhada de vendas realizadas (valor total e quantidade).
* **Ordenação:** Organização automática dos registros por código.

## 🧠 Diferenciais Técnicos

Este projeto foca na implementação de lógica avançada de programação:

* **Recursividade:** As funções de busca (`buscaCodigoRecur`, `buscaNomeRecur`) foram implementadas de forma recursiva, substituindo os laços de repetição tradicionais para localizar itens no array.
* **Structs (Registros):** Uso de `typedef struct` para modelar entidades complexas (`Produto` e `Venda`), relacionando dados de tipos diferentes.
* **Validação de Tipos:** Funções robustas para impedir erros de entrada (ex: digitar letras em campos de preço).
