#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "utils.h"
#include "pessoa.h"
#include "manager.h"

#ifndef FILENAME
#define FILENAME "agenda.dat"
#endif

int main() {
	struct Pessoa pessoa;
	int i = 0;
    char a[] = "brunu";
    i = getElement(a);
    if (i)
        printf("Element found at line %d", i);
    else
        printf("No element found!");
	//menu(&pessoa);

	return 0;
}
