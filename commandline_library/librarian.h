#ifndef LIBRARIAN__HEADER__GUARD
#define LIBRARIAN__HEADER__GUARD
#include "bookStructure.h"
#include "studentStructure.h"

//will create a student with username x and password y, returns 1 if it succeeds 0 if not
int create_student(char x[256], char y[256]);

//will delete the specified student account, returns 1 if it succeeds 0 if not
int delete_student(StudentAccount student);

//following functions could be changed to take an argument with the filename instead however i chose not to

//will create a book list from the file "../booklist.txt"
void open_book_list();

//will create a student list from the file "../studentlist.txt"
void open_account_list();

//will write the book list to the file "../booklist.txt"
void write_book_list();

//will write the student list to the file "../studentlist.txt"
void write_account_list();


#endif