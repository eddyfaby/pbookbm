#ifndef LINKED_H
#define LINKED_H

struct Node;
typedef struct Node *list;
typedef struct Node *pos;
typedef int valType;

struct Node {
    valType value;
    pos next;
};

int isEmpty(list lList);
int isLast(pos lPos);

void criticalError(char *msg);
void printList(list lList, char *msg);

list createList(list pessoa);
void insertNode(valType value, list *lList);

pos findNode(valType value, list lList);
pos findPrev(valType value, list lList);

void deleteNode(valType value, list lList);
list clearList(list lList);

#endif // LINKED_H
