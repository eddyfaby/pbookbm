#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../pessoa.h"
#include "../linked.h"
#include "../utils.h"
#include "../manager.h"

#ifndef FILENAME
#define FILENAME "agenda.dat"
#endif

// menu
void help() {
    puts("\nPara exibir este menu voce pode executar o programa com o parametro -help ou -?"
         "\n"
         "\nFuncoes e sintaxes:"
         "\n"
         "\n -inserir"
         "\n -pesquisar"
         "\n -alterar"
         "\n -deletar"
         "\n"
         "\nInstrucoes das funcoes:"
         "\n"
         "\nInserir   -> Abre um menu solicitando dados para inclusao de um novo"
         "\n             registro."
         "\nPesquisar -> Lista registros de acordo com a busca."
         "\n"
         "\nAlterar   -> Solicita uma busca em que o usuario escolhe um registro"
         "\n             para alteracao."
         "\nDeletar   -> Exclui o registro solicitado."
         "\n"
         "\nImportar  -> Adiciona registros no arquivo atual."
         "\n"
        );
}
void menu(struct Pessoa *pessoa, list *lList) {
    char c;
    puts("Selecione uma opcao \n"
         "[1] Inserir\n"
         "[2] Pesquisar\n"
         "[3] Altera\n"
         "[4] Deleta\n"
         "[5] Ajuda\n"
         "[6] Importar\n"
         "[0] Sair"
        );
    printf("Opcao: ");
    do {
        c = getchar(); cBuff();
    } while (c == '\n');
    switch(c){
        case '1': insert(*pessoa);            break;
        case '2': search(&(*lList));          break;
        case '3': alter(&(*lList));           break;
        case '4': deleteReg(&(*lList));       break;
        case '5': help();                     break;
        case '6': import("");                 break;
        case '0': *lList = clearList(*lList); exit(0);
    }
}
// menu

// Inclusion
int checkName(struct Pessoa pessoa) {
    FILE *file;
    char name[40], *tok;

    if (strlen(pessoa.nome) <= 1)
        return 1;

    file = fopen(FILENAME, "r");
    if (!file) {
    	perror("\nNao foi possivel abrir o arquivo: ");
    	return 1;
    }

    while (fgets(name, sizeof(name), file)) {
        tok = strtok(name, "|");
        strcpy(pessoa.nome, lwrc(pessoa.nome));
        tok = lwrc(tok);
        if (!strcmp(pessoa.nome, tok)) {
            printf("\nEste nome ja foi incluido\nNome: ");
            return 1;
        }
    }
    fclose(file);
    return 0;
}
void resetPessoa(struct Pessoa *pessoa) {
    strcpy(pessoa->nome,     "");
    strcpy(pessoa->endereco, "-");
    strcpy(pessoa->email,    "-");
    strcpy(pessoa->telefone, "-");
    strcpy(pessoa->celular,  "-");
}
void writePerson(struct Pessoa pessoa){
    FILE *file;

    file = fopen(FILENAME, "a+");

    fprintf(file, "%s|", pessoa.nome);
    fprintf(file, "%s|", pessoa.endereco);
    fprintf(file, "%s|", pessoa.email);
    fprintf(file, "%s|", pessoa.telefone);
    fprintf(file, "%s\n", pessoa.celular);

    fclose(file);
}
int askInclusion() {
    char c;
    printf("\nQuer incluir mais registros? (S/N) ");
    c = getchar(); cBuff();
    return (tolower(c) == 's') ? 1 : 0;
}
struct Pessoa readData(struct Pessoa pessoa) {
    resetPessoa(&pessoa);
    printf("Nome: ");
    do {
        scanf("%40[^\n]", pessoa.nome);       cBuff();
    } while (checkName(pessoa));
    printf("Endereco: ");
    scanf("%80[^\n]", pessoa.endereco);   cBuff();
    printf("Email: ");
    scanf("%40[^\n]", pessoa.email);      cBuff();
    printf("Telefone: ");
    scanf("%15[^\n]", pessoa.telefone);   cBuff();
    printf("Celular: ");
    scanf("%15[^\n]", pessoa.celular);    cBuff();
    return pessoa;
}
void insert(struct Pessoa pessoa){
    do{
        writePerson(readData(pessoa));
    } while (askInclusion());
}
// Inclusion

// Search
int listElement(char element[], list *lList) {
    char name[200];
    char *tok = NULL;
    int total = 0;
    int line = 0;
    FILE *file;

    element = lwrc(element);

    file = fopen(FILENAME, "r+");
    if (!file) {
        perror("\nNao foi possivel abrir o arquivo: ");
        return -1;
    }

    while (!feof(file)) {
        line++;
        strcpy(name, "");
        fgets(name, sizeof(name) + sizeof(char), file);
        if (strlen(name) <= 3) continue;
        tok = strtok(name, "|");
        tok = lwrc(tok);
        if (strstr(tok, element)) {
            // create linked list
            insertNode(total, tok, &(*lList));
            printf("\nRegistro #%d", total);
            printf("\nNome    : %s", tok);
            tok = strtok(NULL, "|");
            printf("\nEndereco: %s", tok);
            tok = strtok(NULL, "|");
            printf("\nEmail   : %s", tok);
            tok = strtok(NULL, "|");
            printf("\nTelefone: %s", tok);
            tok = strtok(NULL, "|");
            printf("\nCelular : %s\n", tok);
            ++total;
        }
    }

    fclose(file);

    return total; // n found
}
int getElement(char element[]) {
    char name[40];
    char *tok;
    int line = 0;
    FILE *file;

    element = lwrc(element);

    file = fopen(FILENAME, "r+");
    if (!file) {
        perror("\nNao foi possivel abrir o arquivo: ");
        return -1;
    }
    while (!feof(file)) {
        line++;
        fgets(name, sizeof(name), file);
        tok = strtok(name, "|");
        tok = lwrc(tok);
        if (!strcmp(element, tok)) {
            fclose(file);
            return line; // found
        }
    }

    fclose(file);

    return 0; // nothing found
}
int askSearch() {
    char c;
    printf("\nDeseja realizar uma nova busca? (S/N) ");
    c = getchar(); cBuff();
    return (tolower(c) == 's') ? 1 : 0;
}
void search(list *lList) {
    char name[40];

    do {
        printf("\nDigite o nome: ");
        scanf("%[^\n]", name); cBuff();
        listElement(name, &(*lList));
    } while (askSearch());
}
// Search

// Alter
void alterElement(char element[]) {
    struct Pessoa pessoa;
    deleteElement(element);
    writePerson(readData(pessoa));
}
void alter(list *lList) {
    pos p;
    int i;
    search(&(*lList));
    printf("\nEscolha o registro para alterar (-1 para cancelar): ");
    scanf("%d", &i); cBuff();
    p = findNode(i, *lList);
    if (!p) {
        printf("\nElemento nao encontrado\n");
        return;
    }
    alterElement(p->nome);
    *lList = clearList(*lList);
}
// Alter

// Delete
void deleteElement(char element[]) {
    FILE *t, *f;
    char sLine[201];
    int line = getElement(element);
    int cLine = 0;

    if (line <= 0) {
        printf("\nNenhum elemento foi encontrado\n");
        return;
    }

    f = fopen(FILENAME, "r+");
    if (!f) {
    	perror("\nNao foi possivel abrir o arquivo: ");
    	return;
    }
    t = tmpfile();
    if (!t) {
    	perror("\nNao foi possivel abrir o arquivo: ");
    	return;
    }

    while (fgets(sLine, sizeof(sLine) + sizeof(char), f)) {
        ++cLine;
        if (cLine != line)
            fputs(sLine, t);
    }

    fclose(f);

    f = fopen(FILENAME, "w+");
    if (!f) {
    	perror("\nNao foi possivel abrir o arquivo: ");
    	return;
    }
    rewind(t);

    while (fgets(sLine, 200, t)) {
        fputs(sLine, f);
    }

    fclose(f);
    fclose(t);
}
void deleteReg(list *lList) {
    pos p;
    int i;
    search(&(*lList));
    printf("\nEscolha o registro para deletar (-1 para cancelar): ");
    scanf("%d", &i); cBuff();
    p = findNode(i, *lList);
    if (!p) {
        printf("\nElemento nao encontrado\n");
        return;
    }
    deleteElement(p->nome);
    *lList = clearList(*lList);
}
// Delete

// Import
void import() {
    FILE *f, *t;
    char registro[201];
    char file[201];

    if (strlen(file) < 1) {
        printf("\nDeseja importar de qual arquivo? ");
        scanf("%200[^\n]", file);
    }

    f = fopen(FILENAME, "a+");
    if (!f) {
        perror("Nao foi possivel abrir o arquivo: ");
        return;
    }
    t = fopen(file, "r");
    if (!t) {
        perror("Nao foi possivel abrir o arquivo: ");
        return;
    }
    while (!feof(t)) {
        fgets(registro, sizeof(registro), t);
        fprintf(f, "%s", registro);
    }

    fclose(t);
    fclose(f);
}
// Import
