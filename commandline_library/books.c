#include "bookStructure.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Book* bookList;
int bookListLength = 10;
int initializedCheck = 0;
int booksTotal = 0;

int add_book(char Title[256], char Author[256], char ISBN[256], char Publisher[256]){
    //initialize the book list
    if(initializedCheck != 1){
        bookList = (Book*) malloc(sizeof(Book) * 10);
        initializedCheck = 1;
    }
    
    //expand the list if there is more books than space in the list
    if (booksTotal >= bookListLength){
        bookListLength *= 2;
        bookList = realloc(bookList, sizeof(Book) * bookListLength);
    }    

    //check if the book is already in the list
    for(int n = 0; n < booksTotal; ++n){  
        if (strcmp(bookList[n].ISBN, ISBN) == 0){
            return 0;
        }
    }
    
    //add book to list
    for(int x = 0; x < 256; ++x){
        bookList[booksTotal].Title[x] = Title[x];
        if(Title[x] == '\n'){
            bookList[booksTotal].Title[x] = '\0';
        }
        bookList[booksTotal].Author[x] = Author[x];
        if(Author[x] == '\n'){
            bookList[booksTotal].Author[x] = '\0';
        }
        bookList[booksTotal].ISBN[x] = ISBN[x];
        if(ISBN[x] == '\n'){
            bookList[booksTotal].ISBN[x] = '\0';
        }
        bookList[booksTotal].Publisher[x] = Publisher[x];
        if(Publisher[x] == '\n'){
            bookList[booksTotal].Publisher[x] = '\0';
        }
    }
    bookList[booksTotal].borrowed = false;
    bookList[booksTotal].isBorrowed.false.no = "This book is available in the library";
    
    ++booksTotal;
    return 1;
}
int remove_book(Book book){
    int i = -1;
    //find where the book is in the list
    for(int n = 0; n < booksTotal; ++n){  
        if (strcmp(bookList[n].ISBN, book.ISBN) == 0){
            i = n;
        }
    }
    
    //if the book is borrowed or it doesnt exist dont do anything
    if (i < 0 || bookList[i].borrowed){
        return 1;
    }
    
    //remove the book by moving all books below it up
    for (;i < booksTotal; ++i){
        bookList[i] = bookList[i + 1];
    }
    --booksTotal;
    return 0;
}
char* list_books(int y){
    //make the buffer 256 chars long per book
    char* buff = malloc(sizeof(char) * 256 * booksTotal);
    *buff = '\0';
    //make the string of the title of the books
    if (y == 1){
        for(int i = 0; i < booksTotal; ++i){
            strcat(buff, bookList[i].Title);
            strcat(buff,"\n\n");
        }
    }
    
    //make the string of all information on the book
    if (y == 0){
        for(int i = 0; i < booksTotal; ++i){
            strcat(buff, bookList[i].Title);
            strcat(buff,"\n");
            strcat(buff, bookList[i].Author);
            strcat(buff, "\nISBN: ");
            strcat(buff, bookList[i].ISBN);
            strcat(buff,"\n");
            strcat(buff, bookList[i].Publisher);
            strcat(buff,"\n");
            if (bookList[i].borrowed==false){
                strcat(buff, "This book is available in the library\n");
                strcat(buff, "\n\n");
            } else {
                strcat(buff, "Borrowed");
                strcat(buff, "\n\n");
            }
            
        }
    }
    return buff;
}
char* list_book(int i){
    return bookList[i].Title;
}

int search_books(char isbn[13]){
    for(int i = 0; i < booksTotal; ++i){
        if(strcmp(isbn, bookList[i].ISBN) == 0){
             return i;          
        }
    }
    return -1;
}

char* list_book_full_info(int i){
    char* buff = malloc(sizeof(char) * 256);
    *buff = '\0';
    strcat(buff, bookList[i].Title);
    strcat(buff, "\n");
    strcat(buff, bookList[i].Author);
    strcat(buff, "\nISBN: ");
    strcat(buff, bookList[i].ISBN);
    strcat(buff, "\n");
    strcat(buff, bookList[i].Publisher);
    strcat(buff, "\n");
    if (bookList[i].borrowed==false){
        strcat(buff, "This book is available in the library\n");
        strcat(buff, "\n\n");
    } else {
        strcat(buff, "Borrowed");
        strcat(buff, "\n\n");
    }
    return buff;
}