#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "linked.h"
#include "utils.h"
#include "pessoa.h"
#include "manager.h"

#ifndef FILENAME
#define FILENAME "agenda.dat"
#endif

int main(int argc, char **argv) {
    struct Pessoa person;
    list lList = NULL;

    lList = createList(lList);

    while (1)
        menu(&person, &lList);

    lList = clearList(lList);
	return 0;
}
