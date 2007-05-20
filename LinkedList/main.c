#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../linked.h"
#include "../utils.h"

int isEmpty(list lList) {
    return lList->next == NULL;
}
int isLast(pos lPos) {
  return lPos->next == NULL;
}

void printList(list lList, char *msg) {
    if (lList)
        printf("%s\n", msg);
    else {
        printf("Empty list!");
        return;
    }
    while (lList) {
        printf("Id  : %d\n", lList->id);
        printf("Nome: %s\n", lList->nome);
        lList = lList->next;
    }
}

list createList(list lList) {
    if (lList != NULL)
        return NULL;

    lList = (struct Node *) malloc(sizeof(struct Node) * 1);
    if (!lList) return NULL;

    lList->next = NULL;
    lList->id = 0;
    strcpy(lList->nome, "");

    return lList;
}
void insertNode(valType id, char nome[], list *lList) {
    pos p;

    p = (struct Node *) malloc(sizeof(struct Node));
    if (p == NULL)
        criticalError("There is no space!");

    p->id = id;
    strcpy(p->nome, nome);
    p->next = *lList;
    *lList = p;
}

pos findNode(valType id, list lList) {
    pos p;

    p = lList;
    while (p != NULL && p->id != id) {
        p = p->next;
    }
    return p;
}
pos findPrev(valType id, list lList) {
    pos p;

    p = lList;
    while (p->next != NULL && p->next->id != id) {
        p = p->next;
    }

    return p;
}

void deleteNode(valType id, list lList) {
    pos p, aux;

    p = findPrev(id, lList);

    if (!isLast(p)) {
        aux = p->next;
        p->next = aux->next;
        free(aux);
    }
}
list clearList(list lList) {
    pos p;
    while (lList) {
        p = lList;
        lList = lList->next;
        free(p);
    }
    return NULL;
}
