#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "utils.h"
#include "pessoa.h"
#include "manager.h"
#include "linked.h"

#ifndef FILENAME
#define FILENAME "agenda.dat"
#endif

int main() {
    int i;
	list L = NULL;

	L = createList(L);

	for (i = 1; i <= 10; ++i) {
		insertNode(i, &L);
	}

	printList(L, "Linked List values: ");

    L = clearList(L);

    printList(L, "Is it empty? ");

	return 0;
}
