#ifndef STUDENT__HEADER__GUARD
#define STUDENT__HEADER__GUARD
#include "bookStructure.h"
#include "studentStructure.h"

//will loan the book to the student, returns 1 if fails and 0 if it succeeds
int loan_book(StudentAccount* student, Book* book);

//will return the specified book to the library, returns 0 if it fails and 1 if it succeeds
int return_book(StudentAccount* student, Book* book);

//will return a string of all rented books by the student, if no books are rented it will return '\0'
char* list_rented_books(StudentAccount student);


#endif