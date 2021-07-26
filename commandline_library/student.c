#include "bookStructure.h"
#include "studentStructure.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int loan_book(StudentAccount* student, Book* book){
    if(book->borrowed){
        return 1;
    }
    book->borrowed = true;
    book->isBorrowed.true.yes = "Borrowed";
    for(int i = 0; i < 10; ++i){
        if(student->rentedBooks[i].borrowed != true){
            student->rentedBooks[i] = *book;
            return 0;
        }
    }
}
int return_book(StudentAccount* student, Book* book){
    if(!book->borrowed){
        return 0;
    }  
    for(int i=0; i < 10; ++i){
        //avoid finding a pointer that doesnt exist
        if(student->rentedBooks[i].borrowed == true){
            //find the book to return
            if(strcmp(student->rentedBooks[i].Title, book->Title) == 0){
                student->rentedBooks[i].borrowed = false;          
            }
        }
    }
    book->borrowed = false;
    book->isBorrowed.true.yes = "Borrowed";
    if(book->borrowed == true){
        return 0;
    }
    return 1;
}

char* list_rented_books(StudentAccount student){
    char* buff = malloc(sizeof(char) * 256);
    *buff = '\0';
    for(int i = 0; i < 10; ++i){
        if(student.rentedBooks[i].borrowed == true){
            strcat(buff, student.rentedBooks[i].Title);
            strcat(buff, "\n");
        }
    }
    return buff;
}
