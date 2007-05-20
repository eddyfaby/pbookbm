#ifndef LINKED_H
#define LINKED_H

struct Node;
typedef struct Node *list;
typedef struct Node *pos;
typedef int valType;

struct Node {
    valType id;
    char nome[40];
    pos next;
};

int isEmpty(list lList);
int isLast(pos lPos);

void criticalError(char *msg);
void printList(list lList, char *msg);

list createList(list lList);
void insertNode(valType id, char nome[], list *lList);

pos findNode(valType id, list lList);
pos findPrev(valType id, list lList);

void deleteNode(valType id, list lList);
list clearList(list lList);

#endif // LINKED_H
