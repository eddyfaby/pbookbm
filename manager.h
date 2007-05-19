#ifndef MANAGER_H
#define MANAGER_H

// menu
void menu(struct Pessoa *pessoa);                       // display menu
// menu

// Inclusion
int checkName(struct Pessoa pessoa);                    // check if name is empty
void resetPessoa(struct Pessoa *pessoa);                // set all elements to "-"
void writePerson(struct Pessoa pessoa);                 // write the file
int askInclusion();                                     // check if continue
struct Pessoa readData(struct Pessoa pessoa);           // read person data
void insert(struct Pessoa pessoa);                      // begin insertion
// Inclusion

// Search
int listElement(char element[]);                        // list %element%
int getElement(char element[]);                         // return element line
int askSearch();                                        // check if continue
void search();                                          // do a search
// Search

// Delete
void deleteElement(char element[]);                     // delete a element in the file
// Delete

#endif // MANAGER_H
