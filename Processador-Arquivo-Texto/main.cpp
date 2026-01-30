#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <cstring>

using namespace std;

typedef struct
{
    char pal[50]; // string de at� 50 caracteres
    int contador;
} tparq;

typedef struct Nodo
{
    string palavra;
    int cont;
    struct Nodo *prox;
} Tipolista;

bool acessaArq(string nomearq);
void geraLista(Tipolista **lista, string entrada);
void imprimeLista(Tipolista *lista);
void liberaLista(Tipolista **lista);
void processaArq(string nomearq, Tipolista **lista);
void salvaBin(Tipolista *lista, string nomebin);
void mostraBin(string nomebin);
bool verificaCol(string nome);
int validaInt();
string validaString();
string passaMaiusc(string &texto);
string passaTXT(string nomearq);
string passaBIN(string nomebin);
void retornaMenu();

int main()
{
    int opcao;
    string nomearq, nomebin;
    Tipolista *lista = NULL;
    bool aceTXT = false;
    bool percTXT = false;
    bool impLista = false;
    bool salvouBin = false;

    do
    {
        cout << setw(12) << "Menu" << endl
             << endl;
        cout << "1. Acessar TXT" << endl;
        cout << "2. Percorrer TXT" << endl;
        cout << "3. Imprime lista" << endl;
        cout << "4. Salvar em um arquivo binario" << endl;
        cout << "5. Mostrar conteudo do arquivo" << endl;
        cout << "6. SAIR" << endl
             << endl;

        cout << "Escolha uma opcao, de 1 a 6: ";
        opcao = validaInt();
        cout << endl;

        switch (opcao)
        {

        case 1:
            system("cls");
            cout << "Digite o nome do arquivo: ";
            nomearq = validaString();
            nomearq = passaTXT(nomearq); // adiciona extens�o .TXT

            if (!acessaArq(nomearq))
            {
                cout << "O arquivo nao pode ser aberto ou nao existe :( " << endl
                     << endl;
            }
            else
            {
                if (verificaCol(nomearq))
                {
                    cout << "O arquivo existe, foi aberto com sucesso e possui 30 colunas p/ linha!" << endl
                         << endl;
                    aceTXT = true;
                }
                else
                {
                    cout << "O arquivo existe e foi aberto com sucesso, mas nao possui 30 colunas p/ linha!" << endl
                         << endl;
                    aceTXT = true;
                }
            }
            retornaMenu();
            break;

        case 2:
            system("cls");
            if (!aceTXT)
            {
                cout << "Selecione a opcao 1 (Acessar TXT) antes de percorrer o arquivo!" << endl
                     << endl;
                retornaMenu();
                break;
            }
            processaArq(nomearq, &lista);
            cout << "Arquivo " << nomearq << " percorrido com sucesso!!!" << endl
                 << endl;
            percTXT = true;
            retornaMenu();
            break;

        case 3:
            system("cls");
            if (!percTXT)
            {
                cout << "Selecione a opcao 2 (Percorrer TXT) antes de imprimir a lista!" << endl
                     << endl;
                retornaMenu();
                break;
            }
            imprimeLista(lista);
            impLista = true;
            retornaMenu();
            break;

        case 4:
            system("cls");
            if (!impLista)
            {
                cout << "Selecione a opcao 3 (Imprimir lista) antes de salvar em um arquivo binario!" << endl
                     << endl;
                retornaMenu();
                break;
            }
            cout << "Digite o nome do arquivo binario: ";
            nomebin = validaString();
            nomebin = passaBIN(nomebin); // adiciona extens�o .BIN

            salvaBin(lista, nomebin);
            cout << "Lista salva em " << nomebin << endl;
            liberaLista(&lista); // libera a lista depois de salvar o conte�do no bin�rio
            if (lista == NULL)
            {
                cout << "A lista foi liberada." << endl;
            }
            salvouBin = true;
            retornaMenu();
            break;

        case 5:
            system("cls");
            if (!salvouBin)
            {
                cout << "Selecione a opcao 4 (Salvar em um arquivo binario) antes de mostrar o conteudo do arquivo!" << endl
                     << endl;
                retornaMenu();
                break;
            }
            mostraBin(nomebin);
            retornaMenu();
            break;

        default:
            cout << "Programa encerrado!!!" << endl
                 << endl;
        }

    }
    while (opcao != 6);

    return 0;
}

bool acessaArq(string nomearq)
{
    ifstream arq(nomearq);

    if (arq.is_open())
    {
        arq.close();
        return true; // arquivo existe e pode ser aberto com sucesso
    }
    else
    {
        return false; // arquivo nao existe ou nao pode ser aberto
    }
}

void geraLista(Tipolista **lista, string entrada)
{
    Tipolista *p = *lista;
    Tipolista *pant = NULL;

    while (p != NULL and p->palavra < entrada) // percorre a lista para encontrar a posi��o correta
    {
        pant = p;
        p = p->prox;
    }

    if (p != NULL and p->palavra == entrada) // se a palavra ja existir, incrementa a contagem
    {
        p->cont++;
        return;
    }

    Tipolista *pnovo = new Tipolista; // se a palavra nao for encontrada, cria novo nodo
    pnovo->palavra = entrada;
    pnovo->cont = 1;

    if (pant == NULL) // se a lista estiver vazia ainda
    {
        pnovo->prox = *lista;
        *lista = pnovo; // novo nodo eh o primeiro da lista
    }
    else // se a lista ja tiver algo nela
    {
        pnovo->prox = pant->prox;
        pant->prox = pnovo; // insere o novo nodo na posicao correta
    }
}

void processaArq(string nomearq, Tipolista **lista)
{
    ifstream arq(nomearq);

    if (!arq)
    {
        cout << "Erro ao abrir o arquivo." << endl;
        return;
    }

    string palavra = "";
    char ch;

    while (arq.get(ch))
    {
        if (ch == ' ' or ch == '\n')
        {
            if (palavra.size() >= 5) // verifica se a palavra tem 5 ou mais caracteres
            {
                palavra = passaMaiusc(palavra); //converte a palavra formada pra maiusc
                geraLista(lista, palavra);
            }
            palavra = ""; // reseta a palavra
        }
        else
        {
            palavra += ch; // forma a palavra juntando os chars
        }
    }

    if (palavra.size() >= 5) // se a utlima palavra nao for antes de um espaco ou nova linha
    {
        palavra = passaMaiusc(palavra); //converte a palavra formada pra maiusc
        geraLista(lista, palavra);
    }
    arq.close();
}

void imprimeLista(Tipolista *lista)
{
    Tipolista *p = lista;
    while (p != NULL)
    {
        cout << p->palavra << "  -  " << p->cont << endl
             << endl;
        p = p->prox;
    }
}

void liberaLista(Tipolista **lista)
{
    Tipolista *atual = *lista;
    Tipolista *proximo = NULL;

    while (atual != NULL)
    {
        proximo = atual->prox;
        delete atual;
        atual = proximo;
    }
    *lista = NULL;
}

void salvaBin(Tipolista *lista, string nomebin)
{
    ofstream arqBin(nomebin, ios::binary); // convertendo string para const char*

    if (!arqBin)
    {
        cout << "Erro ao abrir o arquivo binario!!!" << endl;
        exit(0);
    }

    Tipolista *p = lista;
    tparq reg;

    while (p != NULL)
    {
        strcpy(reg.pal, p->palavra.c_str()); // Copia a palavra para reg.pal
        reg.contador = p->cont;

        arqBin.write((char *)&reg, sizeof(tparq)); // Escreve a estrutura tparq
        p = p->prox;
    }

    arqBin.close();
}

void mostraBin(string nomebin)
{
    ifstream arqBin(nomebin, ios::binary); // Convertendo string para const char*

    if (!arqBin)
    {
        cout << "Erro ao abrir o arquivo binario!!!" << endl;
        exit(0);
    }

    tparq reg;

    cout << setw(30) << "CONTEUDO DO ARQUIVO" << endl;

    while (arqBin.read((char *)(&reg), sizeof(tparq)))
    {
        cout << reg.pal << endl;
        cout << reg.contador << endl << endl;
    }
    arqBin.close();
}

bool verificaCol(string nomearq)
{
    ifstream arq(nomearq);

    if (!arq)
    {
        cout << "Erro ao abrir o arquivo" << endl;
        return false;
    }

    string linha;

    while (getline(arq, linha))
    {
        if (linha.length() != 30)
        {
            arq.close();
            return false;
        }
    }

    arq.close();
    return true;
}

int validaInt()
{
    string info;
    int x;
    unsigned int i;
    bool validada;
    do
    {
        validada = true;
        getline(cin, info);
        if (info == "")
            validada = false;
        else if (!isdigit(info[0]))
            validada = false;
        else
            for (i = 1; i < info.length(); i++)
                if (!isdigit(info[i]))
                {
                    validada = false;
                    break;
                }
        if (!validada)
            cout << "Numero invalido, digite novamente." << endl;
    }
    while (!validada);
    x = atoi(info.c_str());

    return x;
}

string validaString()
{
    string info, nome;
    bool validada;
    unsigned int i;
    do
    {
        validada = true;
        getline(cin, info);
        if (info == "")
            validada = false;
        for (i = 0; i < info.length(); i++)
        {
            if (!isalpha(info[i]) && info[i] != ' ' && info[i] != '.')
            {
                validada = false;
                break;
            }
        }
        if (!validada)
            cout << "Entrada invalida, digite novamente" << endl;
    }
    while (!validada);
    nome = info;

    return passaMaiusc(nome);
}

string passaMaiusc(string &texto)
{
    for (unsigned int i = 0; i < texto.size(); ++i) // vai passar por todos os chars da string e passar para maiusculo
    {
        texto[i] = toupper(texto[i]);
    }

    return texto;
}

string passaTXT(string nomearq)
{
    return nomearq += ".TXT";
}

string passaBIN(string nomebin)
{
    return nomebin += ".BIN";
}

void retornaMenu()
{
    cout << endl;
    cout << "<ENTER> 2x para voltar ao menu" << endl;
    cin.ignore();
    cin.get();
    system("cls");
}
