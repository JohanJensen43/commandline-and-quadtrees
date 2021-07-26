#ifndef BOOKS__HEADER__GUARD
#define BOOKS__HEADER__GUARD
#include "bookStructure.h"

//will add a book to a list of books that is dynamically allocated, returns 1 if the book was added and 0 if not
int add_book(char Title[256], char Author[256], char ISBN[256], char Publisher[256]);

//will remove the specified book from the list of books allocated by previous function, returns 0 if the book was removed and 1 if not
int remove_book(Book book);

//will return a string of all books, if y = 1 it will only be the titles and if y = 0 it will be full information, if there are not books it returns '\0'
char* list_books(int y);

//will return the title of book i in the list
char* list_book(int i);

//will return the number of the book that the isbn-13 corresponds to, if no book matches it returns -1
int search_books(char isbn[13]);

//will return a string that lists the full info of the book at location i in the list
char* list_book_full_info(int i);

#endif