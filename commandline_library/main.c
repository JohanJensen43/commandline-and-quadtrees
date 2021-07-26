#include "books.h"
#include "librarian.h"
#include "student.h"
#include "bookStructure.h"
#include "studentStructure.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern StudentAccount studentList[];
extern Book* bookList;
extern int studentAccounts;
char string[256], temp1[256], temp2[256], temp3[256], temp4[256], *stringPointer;
int k, loop, program = 1;

//used for resetting the input buffer
void reset(){
	scanf("%*[^\n]");
	scanf("%*c");
    string[0]='\0';
}

void main () {
    int choice, loggedInAccount = -1;
    StudentAccount account;
    Book book;
    //open the book textfile
    open_book_list();
    //open the account textfile
    open_account_list();

    
    while(program){
        printf("Hello and welcome to the library! \n");
        printf("Please input what you would like to do\n\n");
        printf("1 to log in as a student\n");
        printf("2 to log in as a librarian\n");
        printf("3 to register as a student with the library\n");
        printf("4 to exit the library\n");
        printf("\nPlease input your choice: ");
        
        //if the input is not whats expected keep looping untill the input is what was expected
        while(!scanf("%i", &choice) || choice < 1 || choice > 4){
            reset();
            printf("That was not an option please try again: ");
        }
        //temporary test account


        switch(choice){
            case 1:
                //make sure that no garbage is in the input before asking for username
                reset();
                printf("\n\nPlease input your username: ");
                while(!scanf("%s", string)){
                    reset();
                    printf("You seem to not have input a username try again: ");
                }
                //lets figure out if the account with said username exists
                for(int i = 0; i < studentAccounts; ++i){
                    if (strcmp(string, studentList[i].Username) == 0){
                        loggedInAccount = i;
                    }
                }
                
                //if we found the account with said username ask for password
                if(loggedInAccount != -1){
                    printf("Please input the password for the account \"%s\": ", studentList[loggedInAccount].Username);
                    while(!scanf("%s", string)){
                        reset();
                        printf(": ");
                    }
                    
                    //if password is right (no encryption because thats too much work rn)
                    if(strcmp(string, studentList[loggedInAccount].Password) == 0){
                        loop = 1;
                        while(loop){
                            //interface text
                            printf("\n\n\n\n\nWelcome %s! \n", studentList[loggedInAccount].Username);
                            printf("What would you like to do?\n\n");
                            printf("1. Look and search the libraries books\n");
                            printf("2. Return a book to the library\n");
                            printf("3. Borrow a book from the library\n");
                            printf("4. View the list of books you have borrowed\n");
                            printf("5. Log out and exit\n\n");
                            printf("Input your choice: ");
                            
                            //check input
                            while(!scanf("%i", &choice) || choice < 1 || choice > 5){
                                reset();
                                printf("That was not an option please try again: ");
                            }
                            
                            //sort through the choices
                            switch(choice){
                                
                                
                                case 1:
                                    printf("Looking for a specific book? Input the ISBN-13 and we will find it, otherwise just input anything else and all books will be shown: ");
                                    while(!scanf("%s", string)){
                                        reset();
                                    }
                                    k = search_books(string);
                                    if(k == -1){
                                        stringPointer = list_books(1);
                                        printf("%s", stringPointer);
                                        free(stringPointer);    
                                    } else{
                                        stringPointer = list_book_full_info(k);
                                        printf("%s", stringPointer);
                                        free(stringPointer);
                                    }
                                    reset();
                                    printf("Press Enter to Continue...");
                                    while( getchar() != '\n' );
                                    break;
                                    
                                    
                                case 2:
                                    printf("What is the ISBN-13 of the book you are returning: \n");
                                    while(!scanf("%s", string)){
                                        reset();
                                    }
                                    k = search_books(string);
                                    if(k == -1){
                                        printf("That book doesn't exist within the library\n");
                                    } else{
                                        int g = return_book(&studentList[loggedInAccount], &bookList[k]);
                                        if(g == 0){
                                            printf("This book has already been returned or never borrowed.\n\n");
                                        }else{
                                            printf("The book \"%s\" has been returned. \n\n", bookList[k].Title);
                                        }
                                    }
                                    reset();
                                    printf("Press Enter to Continue...");
                                    while( getchar() != '\n' );
                                    break;
                                    
                                    
                                case 3:
                                    //isbn 13 of the book you wanna borrow
                                    printf("\n\nPlease input the ISBN-13 of the book you intend to borrow: ");
                                    while(!scanf("%s", string)){
                                        reset();
                                    }
                                    //find the book
                                    k = search_books(string);
                                    if(k == -1){
                                        printf("That book doesn't exist within the library\n");
                                    } else {
                                        //loan the book to the student if you can
                                        if(loan_book(&studentList[loggedInAccount], &bookList[k])){
                                            printf("Sorry this book is already borrowed\n\n");
                                        } 
                                        
                                        //else figure out if that was the correct book they wanted to borrow
                                        else{
                                            printf("The book you inputted was \"%s\". Is this correct (yes/no)? ", bookList[k].Title);
                                            while(!scanf("%s", string)){
                                                reset();
                                                
                                            }
                                            if(strcmp(string, "yes") == 0){
                                                printf("Ok, you have borrowed this book!\n\n");
                                            } else {
                                                return_book(&studentList[loggedInAccount], &bookList[k]);
                                                printf("Ok, you have not borrowed this book!\n\n");
                                            }
                                        }
                                    }
                                    reset();
                                    printf("Press Enter to Continue...");
                                    while( getchar() != '\n' );
                                    
                                    break;
                                    
                                    
                                case 4:
                                    stringPointer = list_rented_books(studentList[loggedInAccount]);
                                    printf("The full list of books you have borrowed is: \n%s \n", stringPointer);
                                    free(stringPointer);
                                    reset();
                                    printf("Press Enter to Continue...");
                                    while( getchar() != '\n' );
                                    break;
                                    
                                    
                                case 5:
                                    loop = 0;
                                    break;
                                    
                                default:
                                    printf("If you see this message please tell me how you got here");
                                    break;
                            }
                            
                        } 
                    }
                    
                    //if password is wrong
                    else {
                        loggedInAccount = -1;
                        reset();
                        printf("Wrong password, returning to homescreen\n\n");
                        printf("Press Enter to Continue...");
                        while( getchar() != '\n' );
                        break;
                    }
                } 
                
                //if the account doesnt exist go back to homescreen
                else {
                    reset();
                    printf("\nThat is not an accountname, going back to home screen\n\n");
                    break;
                }
                break;
            case 2:
                reset();
                printf("\n\nPlease input your username: ");
                while(!scanf("%s", string)){
                    reset();
                    printf("You seem to not have input a username try again: ");
                }
     
                if(strcmp(string, "admin") == 0){
                    printf("Please input the password for the account: ");
                    while(!scanf("%s", string)){
                        reset();
                        printf(": ");
                    }
                    
                    
                    if(strcmp(string, "admin") == 0){
                        loop = 1;
                        while(loop){
                            //interface text
                            printf("\n\n\n\n\nWelcome Admin! \n");
                            printf("What would you like to do?\n\n");
                            printf("1. Add a book to the library\n");
                            printf("2. Remove a book from the library\n");
                            printf("3. List all books\n");
                            printf("4. List all students\n");
                            printf("5. Remove a student account from the library\n");
                            printf("6. Log out and exit\n\n");
                            printf("Input your choice: ");
                            //check input
                            while(!scanf("%i", &choice) || choice < 1 || choice > 6){
                                reset();
                                printf("That was not an option please try again: ");
                            }
                            
                            //sort through the choices
                            switch(choice){
                                case 1:
                                    reset();
                                    printf("Enter the name of the book: ");
                                    fgets(temp1, 256, stdin);
                                    printf("Enter the name of the author: ");
                                    fgets(temp2, 256, stdin);
                                    printf("Enter the ISBN-13: ");
                                    fgets(temp3, 256, stdin);
                                    printf("Enter the publisher of the book: ");
                                    fgets(temp4, 256, stdin);
                                    if(add_book(temp1, temp2, temp3, temp4)){
                                        printf("The book was added\n");
                                    } else {
                                        printf("The book was not added, beacuse it already exists\n");
                                    }
                                    printf("Press Enter to Continue...");
                                    while( getchar() != '\n' );
                                    break;
                                    
                                case 2:
                                    printf("Enter the ISBN of the book to be removed: ");
                                    while(!scanf("%s", temp1)){
                                        reset();
                                    }
                                    for(int z = 0; z < 13; ++z){
                                        book.ISBN[z] = temp1[z];
                                    }
                                    if (remove_book(book)){
                                        printf("This book cannot be removed, probably because it is borrowed\n");
                                    } else {
                                        printf("The book was removed\n");
                                    }
                                    reset();
                                    printf("Press Enter to Continue...");
                                    while( getchar() != '\n' );
                                    break;
                                    
                                case 3:
                                    printf("The list of all books is: \n\n");
                                    stringPointer = list_books(0);
                                    printf("%s", stringPointer);
                                    free(stringPointer);
                                    reset();
                                    printf("Press Enter to Continue...");
                                    while( getchar() != '\n' );
                                    break;
                                    
                                case 4:
                                    printf("The list of all student accounts is: \n\n");
                                    for(int z = 0; z < studentAccounts; ++z){
                                        printf("%s \n", studentList[z].Username);
                                    }
                                    reset();
                                    printf("\nPress Enter to Continue...");
                                    while( getchar() != '\n' );
                                    break;
                                    
                                case 5:
                                    printf("Enter the username of the account to be deleted: ");
                                    while(!scanf("%s", string)){
                                        reset();
                                    }
                                    for(int p = 0; p < 256; ++p){
                                        account.Username[p] = string[p];
                                    }
                                    if(delete_student(account)){
                                        printf("This student account has been removed\n");
                                    } else {
                                        printf("This student account has not been removed\n");
                                    }
                                    reset();
                                    printf("Press Enter to Continue...");
                                    while( getchar() != '\n' );
                                    break;
                                    
                                case 6:
                                    loop = 0;
                                    break;
                                    
                                default:
                                    printf("If you see this message please tell me how you got here");
                                    break;
                            }
                        } 
                    }else {
                        printf("Wrong password\n");
                    }
                    
                } else {
                    printf("That is not a librarian account name\n");
                }
                break;
            case 3:   
                
                printf("\n\nPlease input your wanted username: ");
                while(!scanf("%s", string)){
                    reset();
                    printf("You seem to not have input a username try again: ");
                }
                for(int i = 0; i < 256; ++i){
                    temp1[i] = string[i];
                }
                printf("\n\nPlease input your wanted password: ");
                while(!scanf("%s", string)){
                    reset();
                    printf("You seem to not have input a password try again: ");
                }
                for(int i = 0; i < 256; ++i){
                    temp2[i] = string[i];
                }
                if(create_student(temp1, temp2)){
                    reset();
                    printf("This account was created\n");
                } else {
                    printf("This account could not be created try a different username\n");
                }
                printf("Press Enter to Continue...");
                while( getchar() != '\n' );
                
                break;
            case 4:
                program = 0;
                break;
            default:
                printf("If you see this message please tell me how you got here");
                break;
        }
    }
    write_book_list();
    write_account_list();
    free(bookList);
}

