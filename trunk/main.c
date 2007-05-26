#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "pessoa.h"
#include "utils.h"
#include "linked.h"
#include "manager.h"

#ifndef FILENAME
#define FILENAME "agenda.dat"
#endif

int main(int argc, char **argv) {
    struct Pessoa pessoa;
    list lList = NULL;

    lList = createList(lList);

    if (argc > 1) {
        strcpy(argv[1], lwrc(argv[1]));
        if (!strcmp("-inserir", argv[1])) {
            insert(pessoa);
        }
        else if (!strcmp("-pesquisar", argv[1])) {
            search(&lList);
        }
        else if (!strcmp("-alterar", argv[1])) {
            alter(&lList);
        }
        else if (!strcmp("-deletar", argv[1])) {
            deleteReg(&lList);
        }
        else {
            help();
        }
        clearList(lList);
        exit(0);
    }

    while (1)
        menu(&pessoa, &lList);

    lList = clearList(lList);
	return 0;
}
