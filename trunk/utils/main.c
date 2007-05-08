#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void cBuff() {
	char c;
	do {
		fread(&c, sizeof(char), 1, stdin);
	} while (c != '\n' && c != EOF);
}

char* lwrc(char str[]) {
    int i = 0;
    while (str[i]) {
        if (isupper(str[i]))
            str[i] = tolower(str[i]);
        ++i;
    }
    return str;
}
