#include "bookStructure.h"
#include "studentStructure.h"
#include "books.h"
#include "student.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

extern int booksTotal;
extern Book* bookList;
StudentAccount studentList[50];
int studentAccounts = 0;

int create_student(char x[256], char y[256]){
    for(int j = 0; j < studentAccounts; ++j){
        if(strcmp(studentList[j].Username, x) == 0){
            return 0;
        }
    }
    for(int i = 0; i < 256; ++i){
        studentList[studentAccounts].Username[i] = x[i];
        studentList[studentAccounts].Password[i] = y[i];
        if(x[i] == '\n'){
            studentList[studentAccounts].Username[i] = '\0';
        }
        if(y[i] == '\n'){
            studentList[studentAccounts].Password[i] = '\0';
        }
    }
    ++studentAccounts;
    return 1;
}
int delete_student(StudentAccount student){
    int j = -1;
    for(int n = 0; n < studentAccounts; ++n){  
        if (strcmp(studentList[n].Username, student.Username) == 0){
            j = n;
        }
    }
    if(j < 0 || studentList[j].rentedBooks[0].borrowed){
        return 0;
    }
    for (;j < studentAccounts; ++j){
        studentList[j] = studentList[j + 1];
    }
    --studentAccounts;
    return 1;
}
void open_book_list(){
    //buffers to read the file from
    char *characters = calloc(256, sizeof(char));
    char *characters2 = calloc(256, sizeof(char));
    char *characters3 = calloc(256, sizeof(char));
    char *characters4 = calloc(256, sizeof(char));
    char temp1[256], temp2[256], temp3[256], temp4[256];
    //open the file booklist.txt
    FILE *fileToOpen = fopen("../booklist.txt", "r");
    //skip the first line
    fgets(characters, 256, fileToOpen);
    //read the next 4 lines and then create a book from those 4 lines
    do{
        fgets(characters, 256, fileToOpen);
        fgets(characters2, 256, fileToOpen);
        fgets(characters3, 256, fileToOpen);
        fgets(characters4, 256, fileToOpen);
        for(int i = 0; i < 256; ++i){
            temp1[i] = characters[i];
            temp2[i] = characters2[i];
            temp3[i] = characters3[i];
            temp4[i] = characters4[i];
        }
        
        add_book(temp1, temp2, temp3, temp4);
        //skip the space inbetween the books

    }while(fgets(characters, 256, fileToOpen));
    free(characters);
    free(characters2);
    free(characters3);
    free(characters4);
    fclose(fileToOpen);
}
void open_account_list(){
    //open the file studentlist.txt
    FILE *fileToOpen = fopen("../studentlist.txt", "r");
    //buffers to read from the file
    char *characters = calloc(256, sizeof(char));
    char *characters2 = calloc(256, sizeof(char));
    char *characters3 = calloc(256, sizeof(char));
    //skip the first line
    characters = fgets(characters, 256, fileToOpen);
    do{
        //get the username and password and create a student
        fgets(characters, 256, fileToOpen);
        fgets(characters2, 256, fileToOpen);
        create_student(characters, characters2);
        //if the student has any books borrowed add them to his booklist
        for(int i = 0; fgets(characters3, 256, fileToOpen); ++i){
            char searchString[13];
            for(int j = 0; j < 13; ++j){
                searchString[j]=characters3[j];
            }
            int search = search_books(searchString);
            if(search == -1){
                break;
            }
            loan_book(&studentList[studentAccounts-1], &bookList[search]);
        }
    }while(fgets(characters, 256, fileToOpen));
    
    free(characters);
    free(characters2);
    free(characters3);
    fclose(fileToOpen);
}

void write_book_list(){
    //write the booklist to a file
    FILE *fileToWrite = fopen("../booklist.txt", "w");
    fputs("//please do not modify this file", fileToWrite);
    for(int i = 0; i < booksTotal; ++i){
        fputs("\n", fileToWrite);
        fputs(bookList[i].Title, fileToWrite);
        fputs("\n", fileToWrite);
        fputs(bookList[i].Author, fileToWrite);
        fputs("\n", fileToWrite);
        fputs(bookList[i].ISBN, fileToWrite);
        fputs("\n", fileToWrite);
        fputs(bookList[i].Publisher, fileToWrite);
        fputs("\n", fileToWrite);
    }
    fclose(fileToWrite);
}

void write_account_list(){
    //write the account lsit to a file
    FILE *fileToWrite = fopen("../studentlist.txt", "w");
    fputs("//please do not modify this file\n", fileToWrite);
    for(int i = 0; i < studentAccounts; ++i){
        fputs(studentList[i].Username, fileToWrite);
        fputs("\n", fileToWrite);
        fputs(studentList[i].Password, fileToWrite);
        fputs("\n", fileToWrite);
        for(int j = 0; studentList[i].rentedBooks[j].borrowed == true; ++j){
            fputs(studentList[i].rentedBooks[j].ISBN, fileToWrite);
            fputs("\n", fileToWrite);
        }
        if(i < studentAccounts-1)
            fputs("\n\n",fileToWrite);
        else
            fputs("\n", fileToWrite);
    }
    fclose(fileToWrite);
}
