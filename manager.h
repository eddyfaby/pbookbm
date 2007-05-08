#ifndef MANAGER_H
#define MANAGER_H

// menu
void menu(struct Pessoa *pessoa);                       // display menu
// menu

// Inclusion
void resetPessoa(struct Pessoa *pessoa);                // set all elements to "-"
void writePerson(struct Pessoa pessoa);                 // write the file
int askInclusion();                                     // check if continue
struct Pessoa readData(struct Pessoa pessoa);           // read person data
void insert(struct Pessoa pessoa);                      // begin insertion
// Inclusion

// Search
int listElement(char element[], int line);              // list %element%
// Search

// Delete
int getElement(char element[]);                         // find and delete
void delLine(FILE *file, int size);                     // delete a line
// Delete

#endif // MANAGER_H
