#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../utils.h"
#include "../pessoa.h"
#include "../manager.h"

#ifndef FILENAME
#define FILENAME "agenda.dat"
#endif

// menu
void menu(struct Pessoa *pessoa){
    char c;
    puts("Selecione uma opcao \n"
         "[0] Inserir\n"
         "[1] Pesquisar\n"
         "[2] Altera\n"
         "[3] Deleta\n"
         "[4] Sair\n"
         "Opcao: ");
    c = getchar(); cBuff();
    switch(c){
        case '0': insert(*pessoa); break;
        case '1': break;
        case '2': break;
        case '3': break;
        case '4': break;
    }
}
// menu

// Inclusion
void resetPessoa(struct Pessoa *pessoa) {
    strcpy(pessoa->nome,     "-");
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
    printf("Quer incluir mais registros? (S/N) ");
    c = getchar(); cBuff();
    return (tolower(c) == 's') ? 1 : 0;
}
struct Pessoa readData(struct Pessoa pessoa) {
    resetPessoa(&pessoa);
    printf("Pesso: %s", pessoa.nome);
    printf("Nome: ");
    scanf("%40[^\n]", pessoa.nome);       cBuff();
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
int listElement(char element[], int line) {
    char name[40], han[40];
    char *key, *tok;
    int fline = line, total = 0;
    FILE *file;

    file = fopen(FILENAME, "r+");

    while (fline && !feof(file)) {
        fgets(name, sizeof(name), file);
        --fline;
    }
    if (fline > 0) return -1; // invalid line

    while (!feof(file)) {
        line++;
        fgets(name, sizeof(name), file);
        strcpy(han, name);
        tok = strtok(han, "|");
        key = (char *) malloc(sizeof(char *) * strlen(tok));
        strcpy(key, tok);
        key = lwrc(key);
        element = lwrc(element);
        if (strstr(key, element)) {
            // create linked list
            ++total;
        }
        free(key);
    }

    fclose(file);

    return total; // n found
}
int getElement(char element[]) {
    char name[40], han[40];
    char *key, *tok;
    int line = 0;
    FILE *file;

    file = fopen(FILENAME, "r+");
    if (!file) {
        printf("Nao foi possivel ler o arquivo");
        return -1;
    }
    while (!feof(file)) {
        line++;
        fgets(name, sizeof(name), file);
        strcpy(han, name);
        tok = strtok(han, "|");
        key = (char *) malloc(sizeof(char *) * strlen(tok));
        strcpy(key, tok);
        key = lwrc(key);
        element = lwrc(element);
        if (!strcmp(element, key)) {
            fclose(file);
            free(key);
            return line; // found
        }
        free(key);
    }

    fclose(file);

    return 0; // nothing found
}
// Search

// Delete
void deleteElement(char element[]) {
    FILE *t, *f;
    char sLine[201];
    int line = getElement(element);
    int cLine = 0;

    if (line <= 0) {
        printf("\nNenhum elemento foi encontrado");
        return;
    }

    f = fopen(FILENAME, "r+");
    if (!f) {
    	printf("\nNao foi possivel abrir o arquivo");
    	return;
    }
    t = tmpfile();
    if (!t) {
    	printf("\nNao foi possivel abrir o arquivo");
    	return;
    }

    while (fgets(sLine, 200, f)) {
        ++cLine;
        if (cLine != line)
            fputs(sLine, t);
    }

    fclose(f);

    f = fopen(FILENAME, "w+");
    if (!f) {
    	printf("\nNao foi possivel abrir o arquivo");
    	return;
    }
    rewind(t);

    while (fgets(sLine, 200, t)) {
        fputs(sLine, f);
    }

    fclose(f);
    fclose(t);
}
// Delete
