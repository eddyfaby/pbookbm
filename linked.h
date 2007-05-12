#ifndef LINKED_H
#define LINKED_H

struct Node;
typedef struct Node *list;
typedef struct Node *pos;

struct Node {
    int value;
    pos next;
};

int isEmpty(list lList);
int isLast(pos lPos);

void criticalError(char *msg);
void printList(list lList, char *msg);

list createList(list pessoa);
void insertNode(int value, list *lList);

pos findNode(int value, list lList);
pos findPrev(int value, list lList);
int getVal(pos p);

void deleteNode(int value, list lList);
list clearList(list lList);

#endif // LINKED_H
