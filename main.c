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

int main(int argc, char **argv) {
    struct Pessoa person;

    while (1)
        menu(&person);

	return 0;
}
