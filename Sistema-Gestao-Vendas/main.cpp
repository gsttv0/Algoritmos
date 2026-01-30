#include <iostream>
#include <iomanip>
#include <stdlib.h>

#define TMAX 50

using namespace std;

typedef struct {
    string nome;
    int cod; // codigo de cataloga��o
    int qtd = 0;
    float preco;
} Produto;

typedef struct {
    int codProd;
    int qtdVend = 0;
    float valTot = 0;
} Venda;

void incProd(int &n, Produto prod[]);
void consultaProd(int n, Produto prod[]);
void venda(int n, Produto prod[], Venda vendas[], int &nVendas);

void relatorioProd(int n, Produto prod[]);
void relatorioVend(int nVenda, Venda vendas[]);
void relatorios(int n, Produto prod[], int nVendas, Venda vendas[]);

void ordenaProd(int n, Produto prod[]);
void ordenaVenda(int nVendas, Venda vendas[]);

int buscaCodigoRecur(int codigo, int indice, Produto prod[]);
int buscaNomeRecur(string novoProd, int indice, Produto prod[]);
int buscaVendaRecur(int codigo, int vendaInd, Venda vendas[]);

string validaString();
float validaFloat();
int validaInt();
char verificaChar();
int leiaNumInteiroIntervalo(int inf, int sup);

int main() {
    Produto prod[TMAX];
    Venda vendas[TMAX];
    int n = 0;
    int nVendas = 0;
    int opcao;
    bool fechar = false;
    bool prodInc = false;

    do {
        cout << setw(12) << "Menu" << endl;
        cout << "1. Incluir produto" << endl;
        cout << "2. Consultar produto" << endl;
        cout << "3. Vender produto" << endl;
        cout << "4. Gerar relatorio" << endl;
        cout << "5. Sair" << endl << endl;

        cout << "Escolha uma opcao, de 1 a 5: ";
        opcao = leiaNumInteiroIntervalo(1, 5);
        cin.ignore();
        cout << endl;

        switch (opcao) {

        case 1:
            incProd(n, prod);
            prodInc = true;
            break;

        case 2:
           if (!prodInc){
            cout << "INCLUA UM PRODUTO PARA PROSSEGUIR" << endl << endl;
            break;
           }
            consultaProd(n, prod);
            break;

        case 3:
            if (!prodInc){
            cout << "INCLUA UM PRODUTO PARA PROSSEGUIR" << endl << endl;
            break;
           }
            venda(n, prod, vendas, nVendas);
            break;

        case 4:
            if (!prodInc){
            cout << "INCLUA UM PRODUTO PARA PROSSEGUIR" << endl << endl;
            break;
           }
            relatorios(n, prod, nVendas, vendas);
            break;

        case 5:
            cout << "Muito obrigado por usar o programa!" << endl;
            fechar = true;
            break;

        default:
         cout << "OPCAO INVALIDA!";
        }

    } while (not fechar);

    return 0;
}

void incProd(int &n, Produto prod[]) {
    system("cls");
    string novoProd;
    int codigo, un, indice;
    float p;

    if(n >= TMAX){
      cout << "ESTOQUE DE PRODUTOS CHEIO!!!" << endl;
      cout << "ENTER para voltar ao menu";
      cin.get();
      system("cls");
      return;
    }

    cout << "==INFORME OS DADOS DO PRODUTO==" << endl;

    cout << "Nome:" << endl;
    novoProd = validaString();
    indice = buscaNomeRecur(novoProd, n-1, prod); //n-1 pra garantir que a busca comece do ultimo elemento do vet
    if (indice != -1){
      cout << "Ja existe um produto com este nome!" << endl << endl;
      cout << "ENTER para voltar ao menu";
      cin.get();
      system("cls");
      return;
    }

    cout << "Codigo de Catalogacao:" << endl;
    codigo = validaInt();
    indice = buscaCodigoRecur(codigo, n - 1, prod); //n-1 pra garantir que a busca comece do ultimo elemento do vet
    if (indice != -1){
        cout << "Ja existe um produto com este codigo de catalogacao!" << endl << endl;
        cout << "ENTER para voltar ao menu";
        cin.get();
        system("cls");
        return;
    }

    prod[n].nome = novoProd;
    prod[n].cod = codigo;

    cout << "Quantidade: " << endl;
    un = validaInt();
    prod[n].qtd += un;

    cout << "Preco: " << endl;
    p = validaFloat();
    prod[n].preco = p;
    cout << endl;
    n++;

    ordenaProd(n, prod);
    cout << "ENTER para voltar ao menu";
    cin.get();
    system("cls");
}

void consultaProd(int n, Produto prod[]) {
    system("cls");
    int codigo, indice;
    cout << "==DIGITE O CODIGO==" << endl;
    codigo = validaInt();
    indice = buscaCodigoRecur(codigo, n - 1, prod);
      //verificar funcionamento da pesquisa
    if (indice != -1) { // Se o c�digo foi encontrado
        cout << "Nome: " << prod[indice].nome << endl;
        cout << "Codigo: " << prod[indice].cod << endl;
        cout << "Unidades no estoque: " << prod[indice].qtd << endl;
        cout << "Preco de venda: R$" << prod[indice].preco << endl << endl;
        cout << "ENTER para voltar ao menu";
        cin.get();
        system("cls");
    }

    if (indice == -1) {
        cout << "!PRODUTO INEXISTENTE!" << endl << endl;
        cout << "ENTER para voltar ao menu";
        cin.get();
        system("cls");
    }
}

void venda(int n, Produto prod[], Venda vendas[], int &nVendas) {
    system("cls");
    char resp;
    int codigo, quant;
    float totalVend;

    cout << "==VENDA DO PRODUTO==" << endl << endl;

    cout << "Codigo de Catalogacao: " << endl;
    codigo = validaInt();
    int indice = buscaCodigoRecur(codigo, n - 1, prod);
    if (indice == -1) {
        cout << endl;
        cout << "!PRODUTO INEXISTENTE!" << endl << endl;
        cout << "ENTER para voltar ao menu";
        cin.get();
        system("cls");
        return;
    }

    if (prod[indice].qtd == 0) {// verifica se o produto tem estoque pra venda
        cout << "Produto fora de estoque!" << endl;
        cout << "Deseja comprar outro produto? (S/N): ";
        resp = verificaChar();
        if (toupper(resp) != 'S') {
            cout << "VENDA CANCELADA!!!" << endl << endl;
            cout << "ENTER para voltar ao menu";
            cin.get();
            system("cls");
            return;
        } else {
            venda(n, prod, vendas, nVendas); // repete a func de venda para a compra de outro produto
            return;
        }
    }

    cout << "Quantidade desejada: " << endl;
    quant = validaInt();

    if (quant > prod[indice].qtd) {// verifica se a qtd desejada ta disponivel
        cout << "Quantidade insuficiente, so temos " << prod[indice].qtd << " UN no estoque!" << endl;
        cout << "Serao vendidas " << prod[indice].qtd << " un: " << endl;
        quant = prod[indice].qtd;
    }

    totalVend = quant * prod[indice].preco;

    do {
        cout << "==INFORMACOES DA VENDA==" << endl << endl;
        cout << "Nome: " << prod[indice].nome << endl;
        cout << "Codigo: " << codigo << endl;
        cout << "Quantidade Vendida: " << quant << endl;
        cout << "Preco total da venda: R$" << totalVend << endl << endl;
        cout << "Confirmar Venda: S(SIM) / N(NAO)? " << endl;
        resp = verificaChar();
    } while (toupper(resp) != 'S' and toupper(resp) != 'N');

    if (toupper(resp) == 'S') {
        prod[indice].qtd -= quant;
        cout << "VENDA REALIZADA!!!" << endl << endl;
        cout << "Quantidade restante de " << prod[indice].nome << " eh de " << prod[indice].qtd << " UN" << endl << endl;

        int vendaInd = buscaVendaRecur(codigo, nVendas - 1, vendas); // funcao rec pra verificar se o prod ja foi vendido antes
        if (vendaInd != -1) {
            vendas[vendaInd].qtdVend += quant;
            vendas[vendaInd].valTot += totalVend;
        } else {
            vendas[nVendas].codProd = codigo;
            vendas[nVendas].qtdVend = quant;
            vendas[nVendas].valTot = totalVend;
            nVendas++;
        }

        ordenaVenda(nVendas, vendas);

        cout << "ENTER para voltar ao menu";
        cin.get();
        system("cls");

    } else {
        cout << "VENDA CANCELADA!!!" << endl << endl;
        cout << "ENTER para voltar ao menu";
        cin.get();
        system("cls");
    }
}


void relatorioProd(int n, Produto prod[]){
   cout << "==RELATORIO - PRODUTOS NO ESTOQUE==" << endl << endl;
   for (int i=0; i<n; i++){
        cout << "Nome: " << prod[i].nome << endl;
        cout << "Codigo: " << prod[i].cod << endl;
        cout << "Quantidade: " << prod[i].qtd << endl;
        cout << "Preco: R$" << prod[i].preco << endl;
        cout << endl;
   }
}

void relatorioVend(int nVenda, Venda vendas[]){
   cout << "==RELATORIO - VENDAS==" << endl << endl;
   for(int i=0; i < nVenda; i++){
      cout << "Codigo do produto: " << vendas[i].codProd << endl;
      cout << "Total vendido: " << vendas[i].qtdVend << endl;
      cout << "Valor total vendido: R$" << vendas[i].valTot << endl;
      cout << endl;
   }
}

void relatorios(int n, Produto prod[], int nVendas, Venda vendas[]) { //faz verifica��o e imprime os relatorios necessarios
    system("cls");
    if (nVendas > 0) {
        relatorioProd(n, prod);
        relatorioVend(nVendas, vendas);
        cout << "ENTER para voltar ao menu";
        cin.get();
        system("cls");
    } else {
        relatorioProd(n, prod);
        cout << "ENTER para voltar ao menu";
        cin.get();
        system("cls");
    }
}

string validaString() {
    string info, nome;
    bool validada;
    unsigned int i;
    do {
        validada=true;
        getline(cin, info);
        if (info == "")
            validada = false;
        for (i = 0; i < info.length(); i++)
            if (!isalpha(info[i]) && info[i] != ' ')
                validada = false;
        if (!validada)
            cout << "Entrada invalida, digite novamente" << endl;
    } while (!validada);

    for (i = 0; i < info.length(); i++) { //conversao dos char para maisculo
        info[i] = toupper(info[i]);
    }

    nome = info;
    return nome;
}


float validaFloat() {
    string info;
    float n;
    unsigned int i, ponto;
    bool validada;
    do {
        validada = true;
        ponto = 0;
        getline(cin, info);
        if (info == "")
            validada = false;
        else if (!isdigit(info[0]))
            validada = false;
        else
            for (i = 1; i < info.length(); i++)
                if (!isdigit(info[i])) {
                    if (isdigit(info[i - 1]) && info[i] == '.' && ponto == 0)
                        ponto++;
                    else {
                        validada = false;
                        break;
                    }
                }
        if (!validada)
            cout << "Preco invalido, digite novamente." << endl; // adaptado para preco
    } while (!validada);
    n = stof(info);
    return n;
}

int validaInt() {
    string info;
    int x;
    unsigned int i;
    bool validada;
    do {
        validada = true;
        getline(cin, info);
        if (info == "")
            validada = false;
        else if (!isdigit(info[0]))
            validada = false;
        else
            for (i = 1; i < info.length(); i++)
                if (!isdigit(info[i])) {
                    validada = false;
                    break;
                }
        if (!validada)
            cout << "Numero invalido, digite novamente." << endl;
    } while(!validada);
    x = stoi(info);
    return x;
}

int leiaNumInteiroIntervalo(int inf, int sup) {
    int n;
    do {
        cin >> n;
        if (n < inf || n > sup)
            cout << "Nao esta no intervalo solicitado!! " << endl;
    } while (n < inf || n > sup);
    return n;
}


char verificaChar() {
    bool validada;
    char letra;
    do {
        validada = true;
        letra = toupper(cin.get());
        if (letra == ' ')
            validada = false;
        else if (letra != 'S' and letra != 'N')
            validada = false;
        if (!validada){
            cout << "Entrada invalida! Digite somente S ou N!" << endl << endl;
            cin.ignore();
        }


    } while (!validada);
    cin.ignore();
    return letra;

}


void ordenaProd(int n, Produto prod[]) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            // verifica se o cod do produto atual eh maior que o cod do proximo produto
            if (prod[j].cod > prod[j + 1].cod) {
                // Troca os produtos de posicao
                Produto aux = prod[j];
                prod[j] = prod[j + 1];
                prod[j + 1] = aux;
            }
        }
    }
}
void ordenaVenda(int nVendas, Venda vendas[]) {
    for (int i = 0; i < nVendas - 1; i++) {
        for (int j = 0; j < nVendas - i - 1; j++) {
            // verifica se o cod do produto atual eh maior que o cod do proximo produto
            if (vendas[j].codProd > vendas[j + 1].codProd) {
                // Troca os produtos de posicao
                Venda aux = vendas[j];
                vendas[j] = vendas[j + 1];
                vendas[j + 1] = aux;
            }
        }
    }
}

int buscaCodigoRecur(int codigo, int indice, Produto prod[]) {
    if (indice < 0) { // caso indice for menor que o vet todo
        return -1; // -1 para nao encontrado
    }
    if (prod[indice].cod == codigo) {//se o indice atual eh igual ao codigo buscado
        return indice; // retorna o indice do codigo
    }
    return buscaCodigoRecur(codigo, indice - 1, prod); //chama a func novamente para verificar o proximo indice
}


int buscaNomeRecur(string novoProd, int indice, Produto prod[]) {
    if (indice < 0) {
        return -1;
    }
    if (prod[indice].nome == novoProd) {
        return indice;
    }
    return buscaNomeRecur(novoProd,indice-1,prod);
}

int buscaVendaRecur(int codigo, int vendaInd, Venda vendas[]){
   if(vendaInd < 0){
      return -1;
   }
   if (vendas[vendaInd].codProd == codigo){
      return vendaInd;
   }
   return buscaVendaRecur(codigo, vendaInd-1, vendas);
}
