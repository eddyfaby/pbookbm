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
        if (!strcmpi("-help", argv[1]) || !strcmpi("-?", argv[1])) {
            help();
        }
        if (!strcmpi("-inserir", argv[1])) {
            insert(pessoa);
        }
        if (!strcmpi("-pesquisar", argv[1])) {
            search(&lList);
        }
        if (!strcmpi("-alterar", argv[1])) {
            alter(&lList);
        }
        if (!strcmpi("-deletar", argv[1])) {
            deleteReg(&lList);
        }
        clearList(lList);
        exit(0);
    }

    while (1)
        menu(&pessoa, &lList);

    lList = clearList(lList);
	return 0;
}
