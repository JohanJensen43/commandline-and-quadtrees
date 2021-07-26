#ifndef FUNCTIONS_TO_TEST_H__GUARD
#define FUNCTIONS_TO_TEST_H__GUARD
#include "bookStructure.h"
#include "studentStructure.h"

int add_book(char Title[256], char Author[256], char ISBN[256], char Publisher[256]);

int remove_book(Book book);

int loan_book(StudentAccount* student, Book* book);

int return_book(StudentAccount* student, Book* book);

void list_rented_books(StudentAccount student);

char* list_books(int y);

char* list_book(int i);

int create_student(char x[256], char y[256]);

int delete_student(StudentAccount student);


#endif