#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#define TMAX 30

using namespace std;

void incluirLivro(string titulo[], string autor[], string editora[], string isbn[], int qtdEx[], int& item);
void consultaLivro(string titulo[], string autor[], string editora[], string isbn[], int qtdEx[], int item);
void excluirLivro(string titulo[], string autor[], string editora[], string isbn[], int qtdEx[], int& item);
void adLivro(string isbn[], int qtdEx[], int item);
void relatorio(string titulo[], string autor[], string editora[], string isbn[], int qtdEx[], int item);
int validaInt();
string validaString();
string validaISBN();
string passaMaiusc(string& texto);

int main()
{
    int opcao;
    int item = 0;
    string titulo[TMAX], autor[TMAX], editora[TMAX], isbn[TMAX];
    int qtdEx[TMAX];

    do
    {
        cout<<setw(12)<<"Menu"<<endl<<endl; //setw serve para alinha o "Menu", com 12 espacos atras e 12 na frente
        cout << "1. Incluir livro" <<endl;
        cout << "2. Consultar livro"<<endl;
        cout << "3. Adquirir livro"<<endl;
        cout << "4. Excluir livro"<<endl; // vai excluir o titulo do acervo, ou seja, bye bye todo o conteudo do livro
        cout << "5. Gerar relatorio"<<endl;
        cout << "6. Sair" <<endl<<endl;

        cout<<"Escolha uma opcao, de 1 a 6: ";
        opcao = validaInt();
        cout<<endl;


        switch(opcao)
        {

        case 1:
            incluirLivro(titulo, autor, editora, isbn, qtdEx, item);
            break;

        case 2:
            consultaLivro(titulo, autor, editora, isbn, qtdEx, item);
            break;

        case 3:
            adLivro(isbn, qtdEx, item);
            break;

        case 4:
            excluirLivro(titulo, autor, editora, isbn, qtdEx, item);
            break;

        case 5:
            relatorio(titulo, autor, editora, isbn, qtdEx, item);
            break;

        default:
            cout<<"Programa encerrado!!!"<<endl<<endl;
        }

    }
    while(opcao != 6);
    return 0;
}

void incluirLivro(string titulo[], string autor[], string editora[], string isbn[], int qtdEx[], int& item)
{
    int qtd; // variavel codigo recebe o valor de ISBN
    string t, a, e, codigo;

    if (item >= TMAX)
    {
        cout << "O acervo está cheio. Não é possível adicionar mais livros." << endl << endl;
        return;
    }

    cout << "Informe o ISBN-13 do livro (0000000000000): ";
    codigo = validaISBN();

    for(int i=0; i< item; i++)
    {
        if(codigo == isbn[i])
        {
            cout << "Livro ja existe no acervo!" << endl << endl;
            return;
        }
    }
    isbn[item]=codigo;

    cout << "Informe o titulo do livro: ";
    t = validaString();
    titulo[item]=t;


    cout << "Informe o autor do livro: ";
    a = validaString();
    autor[item]=a;


    cout << "Informe a editora do livro: ";
    e = validaString();
    editora[item]=e;


    do
    {
        cout << "Informe a quantidade de exemplares: ";
        qtd = validaInt();
    }
    while(qtd<=0);

    qtdEx[item]= qtd;
    cout << endl;
    cout << "Livro Incluido com sucesso!!!" << endl << endl;
    item++;
}

void consultaLivro (string titulo[], string autor[], string editora[], string isbn[], int qtdEx[], int item)
{
    string codigo;
    bool encontrado = false;

    cout << "Informe o ISBN-13 do livro (0000000000000): ";
    codigo = validaISBN();

    for(int i=0; i< item; i++)
    {
        if(codigo == isbn[i])
        {
            cout << "INFORMACOES" << endl << endl;
            cout << "ISBN-13: " << isbn[i] << endl;
            cout << "Titulo: " << titulo[i] << endl;
            cout << "Autor: " << autor[i] << endl;
            cout << "Editora: " << editora[i] << endl;
            cout << "Quantidade de exemplares: " << qtdEx[i] << endl;

            encontrado = true;
            break;
        }
    }
    if(!encontrado)
    {
        cout << "LIVRO INEXISTENTE" << endl << endl;
    }
}

void excluirLivro(string titulo[], string autor[], string editora[], string isbn[], int qtdEx[], int& item)
{
    string codigo;
    bool encontrado = false;

    cout << "Informe o ISBN-13 do livro a ser excluido (0000000000000): ";
    codigo = validaISBN();
    cout << endl;


    for (int i = 0; i < item; i++)
    {
        if (codigo == isbn[i])
        {
            for (int j = i; j < item - 1; j++)
            {
                isbn[j] = isbn[j + 1];             // Removendo o livro da lista movendo os elementos para trás
                titulo[j] = titulo[j + 1];
                autor[j] = autor[j + 1];
                editora[j] = editora[j + 1];
                qtdEx[j] = qtdEx[j + 1];
            }
            encontrado = true;
            break;
        }
    }
    if (encontrado)
    {
        cout << "Livro excluido com sucesso!!!" << endl << endl;
        item--; // Reduzindo o contador de itens
    }
    else
    {
        cout << "Livro nao encontrado." << endl << endl;
    }
}

void adLivro(string isbn[], int qtdEx[], int item)
{
    int add = 0;
    bool encontrado = false;
    string codigo;

    cout << "Informe o ISBN-13 do livro a ser inserido (0000000000000): ";
    codigo = validaISBN();

    for (int i = 0; i < item; i++)
    {
        if(codigo == isbn[i])
        {
            encontrado = true;

            cout << "LIVRO ENCONTRADO" << endl;

            cout << "Quantidade de exemplares a serem inseridos: ";
            add = validaInt();

            qtdEx[i] += add;

            cout << "Livros adquiridos!!!" << endl << endl;
            cout << "Quantidade atual de exemplares: " << qtdEx[i] << endl << endl;
            break;
        }
    }
    if (!encontrado)
    {
        cout << "Livro Inexistente" << endl << endl;
    }
}
void relatorio(string titulo[], string autor[], string editora[], string isbn[], int qtdEx[], int item)
{
    if (item < 1)
    {
        cout << "NENHUM LIVRO NO ACERVO!!!" << endl << endl;
        return;
    }

    for(int i=0; i < item - 1; i++)  //item-1 para comparar ate o penultimo
    {
        for(int j=0; j < item - i - 1; j++)  //esse item -i-1 garante que os itens que j foram movidos para sua posicao certa nao sejam incluidos / nao seja feita comparacao desnecessaria
        {
            if (titulo[j] > titulo[j+1])
            {

                swap(titulo[j], titulo[j+1]);

                swap(autor[j], autor[j+1]);

                swap(editora[j], editora[j+1]);

                swap(isbn[j], isbn[j+1]);

                swap(qtdEx[j], qtdEx[j+1]);
            }
        }
    }

    cout << setw(12) << "RELATORIO DO ACERVO" << endl << endl;
    for(int i=0; i < item; i++)
    {
        cout << i+1 << "o Livro" << endl << endl;
        cout << "Titulo: " << titulo[i] <<endl;
        cout << "Autor: " << autor[i] <<endl;
        cout << "Editora: " << editora[i] <<endl;
        cout << "ISBN-13: " << isbn[i] <<endl;
        cout << "Quantida de Exemplares: " << qtdEx[i] <<endl << endl;
    }
}
int validaInt()
{
    string info;
    int x;
    unsigned int i;
    bool validada;
    do
    {
        validada=true;
        getline(cin,info);
        if(info=="")
            validada=false;
        else if(!isdigit(info[0]))
            validada=false;
        else
            for(i=1; i<info.length(); i++)
                if(not isdigit(info[i]))
                {
                    validada=false;
                    break;
                }
        if(not validada)
            cout <<"Numero invalido, digite novamente."<<endl;
    }
    while(not validada);
    x=atoi(info.c_str());

    return x;
}

string validaString()
{
    string info, nome;
    bool validada;
    unsigned int i;
    do
    {
        validada=true;
        getline(cin,info);
        if(info=="")
            validada= false;
        for(i=0; i<info.length(); i++)
            if(not isalpha(info[i]) and info[i]!=' ')
                validada= false;
        if(not validada)
            cout <<"Entrada invalida, digite novamente"<< endl;
    }
    while(not validada);
    nome = info;

    return passaMaiusc(nome);
}
string validaISBN()
{
    string info, codigo;
    bool validada = false;
    unsigned int i;

    do
    {
        validada = true;
        getline(cin,info);
        if (info.size() != 13) // se a string tiver um tamanho diferente de 13, da invalida
            validada = false;
        for(i=0; i<info.size(); i++) // percorre a string do isbn toda, caso algum não seja digito, da invalida
        {
            if(not isdigit(info[i]))
                validada = false;
            if (not validada)
            {
                cout << "ISBN-13 invalido, digite novamente"<< endl;
                break;
            }
        }
    }
    while(not validada);
    codigo = info;

    return codigo;
}

string passaMaiusc(string& texto)
{

    for (unsigned int i = 0; i < texto.size(); ++i)   //vai passar por todos os chars da string e passar para maiusculo
    {
        texto[i] = toupper(texto[i]);
    }

    return texto;
}
