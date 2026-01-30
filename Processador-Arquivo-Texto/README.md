# Processador de Frequência de Palavras e Arquivos Binários 📄💾

Projeto em C++ focado na manipulação avançada de arquivos e estruturas de dados dinâmicas. O software lê um arquivo de texto, processa suas palavras, contabiliza a frequência de cada uma e permite a persistência dos dados em formato binário.

## 🚀 Funcionalidades

* **Leitura de Texto (.txt):** Abre e percorre arquivos de texto caractere por caractere.
* **Processamento de Strings:**
    * Filtra palavras com menos de 5 caracteres.
    * Converte automaticamente para maiúsculas.
    * Ignora espaços e quebras de linha.
* **Lista Encadeada Ordenada:** As palavras são inseridas em uma lista encadeada dinâmica (`Linked List`), mantendo a ordem alfabética automaticamente (Insertion Sort) e incrementando o contador se a palavra já existir.
* **Persistência Binária (.bin):**
    * Serialização: Salva a estrutura da lista em um arquivo binário para economia de espaço e segurança.
    * Leitura: Capaz de ler o arquivo binário gerado e reconstruir/exibir os dados.

## 🧠 Destaques Técnicos

* **Gestão de Memória:** Uso intensivo de ponteiros e alocação dinâmica (`new`/`delete`) para criar e limpar os nós da lista.
* **Manipulação de Arquivos (`fstream`):** Uso das flags `ios::binary`, `read` e `write` para manipular dados brutos, além do padrão `ifstream` para texto.
* **Structs:** Definição de estruturas para o nó da lista (`Tipolista`) e para o registro binário (`tparq`).
