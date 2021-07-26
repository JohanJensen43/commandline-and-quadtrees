#include "functions_to_test.h"
#include <string.h>
#include "unity.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern int studentAccounts;
extern StudentAccount studentList[];

void test_add_book(){
    Book book = {"The Lord of the Rings: The Fellowship of the Ring", "J. R. R. Tolkien", "9780007488315", "HarperCollins Publishers Ltd"};
    book.isBorrowed.false.no = "Book is available in the library";
    TEST_ASSERT_TRUE_MESSAGE(add_book(book.Title, book.Author, book.ISBN, book.Publisher), "Succesfully adding the book should return true");
    TEST_ASSERT_FALSE_MESSAGE(add_book(book.Title, book.Author, book.ISBN, book.Publisher), "Trying to add the same book should return false");
    TEST_ASSERT_EQUAL_STRING_MESSAGE(book.Title, list_book(0), "Book does not show up in the first location of the list");
}

void test_remove_book(){
    Book book = {"The Lord of the Rings: The Fellowship of the Ring", "J. R. R. Tolkien", "9780007488315", "HarperCollins Publishers Ltd"};
    add_book(book.Title, book.Author, book.ISBN, book.Publisher);
    TEST_ASSERT_FALSE_MESSAGE(remove_book(book), "remove book should return 0 if the book is removed");
    TEST_ASSERT_TRUE_MESSAGE(remove_book(book), "remove book should return 1 if the book doesn't exist");
    Book book2 = {"The Lord of the Rings: The Two Towers", "J. R. R. Tolkien", "9780007488339", "HarperCollins Publishers Ltd"};
    Book book3 = {"The Lord of the Rings: The Return of the King", "J. R. R. Tolkien", "9780007488353", "HarperCollins Publishers Ltd"};
    book3.borrowed = true;
    book3.isBorrowed.true.yes = "Borrowed by: Placeholder";
    add_book(book.Title, book.Author, book.ISBN, book.Publisher);
    add_book(book2.Title, book2.Author, book2.ISBN, book2.Publisher);
    add_book(book3.Title, book3.Author, book3.ISBN, book3.Publisher);
    TEST_ASSERT_FALSE_MESSAGE(remove_book(book2), "remove book should return 0 if the book is removed");
    TEST_ASSERT_TRUE_MESSAGE(remove_book(book2), "remove book should return 1 if the book doesn't exist");
    TEST_ASSERT_TRUE_MESSAGE(remove_book(book3), "book should not be able to be removed it is borrowed");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("The Lord of the Rings: The Fellowship of the Ring\n\nThe Lord of the Rings: The Return of the King\n\n", list_books(1), "book 1 and book 3 does not show up in the list");
    book3.borrowed = false;
    TEST_ASSERT_FALSE_MESSAGE(remove_book(book), "book should be removed and the function should return 0");
    TEST_ASSERT_FALSE_MESSAGE(remove_book(book3), "book should be removed and function should return 0");
}

void test_loan_book(){
    StudentAccount testStudent = {"Placeholder", "Placeholder"};
    StudentAccount testStudent2 = {"Placeholder2", "Placeholder2"};
    Book book = {"The Lord of the Rings: The Fellowship of the Ring", "J. R. R. Tolkien", "9780007488315", "HarperCollins Publishers Ltd", false};
    Book book2 = {"The Lord of the Rings: The Two Towers", "J. R. R. Tolkien", "9780007488339", "HarperCollins Publishers Ltd", false};
    Book book3 = {"The Lord of the Rings: The Return of the King", "J. R. R. Tolkien", "9780007488353", "HarperCollins Publishers Ltd", false};
    book.borrowed = true;
    book.isBorrowed.true.yes = "Borrowed";
    book2.borrowed = true;
    book2.isBorrowed.true.yes = "Borrowed";
    TEST_ASSERT_TRUE_MESSAGE(loan_book(&testStudent2, &book), "loan book should return 1 if the book is already borrowed");
    loan_book(&testStudent2, &book3);
    TEST_ASSERT_EQUAL_STRING_MESSAGE("Borrowed", book3.isBorrowed.true.yes, "The book is supposed to be loaned by Placeholder2 but is never set that way");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("Borrowed", book.isBorrowed.true.yes, "The book  was already loaned to a student but was overwritten by another student");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("Borrowed", book2.isBorrowed.true.yes, "The book  is no longer loaned to the studen that loaned it");
    TEST_ASSERT_EQUAL_INT_MESSAGE(true, book.borrowed, "Book 1 is supposed to borrowed it is no longer marked as such");
    TEST_ASSERT_EQUAL_INT_MESSAGE(true, book2.borrowed, "Book 2 is supposed to borrowed it is no longer marked as such");
    TEST_ASSERT_EQUAL_INT_MESSAGE(true, book3.borrowed, "Book 2 is supposed to borrowed it is no longer marked as such");
}

void test_return_book(){
    StudentAccount testStudent = {"Placeholder", "Placeholder"};
    StudentAccount testStudent2 = {"Placeholder2", "Placeholder2"};
    Book book = {"The Lord of the Rings: The Fellowship of the Ring", "J. R. R. Tolkien", "9780007488315", "HarperCollins Publishers Ltd"   };
    Book book2 = {"The Lord of the Rings: The Two Towers", "J. R. R. Tolkien", "9780007488339", "HarperCollins Publishers Ltd"};
    Book book3 = {"The Lord of the Rings: The Return of the King", "J. R. R. Tolkien", "9780007488353", "HarperCollins Publishers Ltd"};
    book.borrowed = true;
    book.isBorrowed.true.yes = "Borrowed by: Placeholder";
    book2.borrowed = true;
    book2.isBorrowed.true.yes = "Borrowed by: Placeholder";
    book3.borrowed = true;
    book3.isBorrowed.true.yes = "Borrowed by: Placeholder2";
    TEST_ASSERT_TRUE_MESSAGE(return_book(&testStudent, &book), "If the book is succesfully returned return_book should return 1");
    TEST_ASSERT_FALSE_MESSAGE(return_book(&testStudent, &book), "if the book cannot be returned return_book should return 0");
    TEST_ASSERT_EQUAL_INT_MESSAGE(0 , book.borrowed, "Book was not returned properly");
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, book2.borrowed, "return_book returned more books than supposed to");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("Borrowed by: Placeholder2", book3.isBorrowed.true.yes, "return_book touched another books information");
}

void test_list_books(){
    Book book = {"The Lord of the Rings: The Fellowship of the Ring\n", "J. R. R. Tolkien\n", "9780007488315\n", "HarperCollins Publishers Ltd\n"};
    add_book(book.Title, book.Author, book.ISBN, book.Publisher);
    Book book2 = {"The Lord of the Rings: The Two Towers\n", "J. R. R. Tolkien\n", "9780007488339\n", "HarperCollins Publishers Ltd\n"};
    add_book(book2.Title, book2.Author, book2.ISBN, book2.Publisher);
    Book book3 = {"The Lord of the Rings: The Return of the King\n", "J. R. R. Tolkien\n", "9780007488353\n", "HarperCollins Publishers Ltd\n"};
    add_book(book3.Title, book3.Author, book3.ISBN, book3.Publisher);
    char c[500];
    strcat(c, "The Lord of the Rings: The Fellowship of the Ring\n");
    strcat(c, "J. R. R. Tolkien\n");
    strcat(c, "ISBN: 9780007488315\n");
    strcat(c, "HarperCollins Publishers Ltd\n");
    strcat(c, "This book is available in the library\n");
    strcat(c, "\n\n");
    strcat(c, "The Lord of the Rings: The Two Towers\n");
    strcat(c, "J. R. R. Tolkien\n");
    strcat(c, "ISBN: 9780007488339\n");
    strcat(c, "HarperCollins Publishers Ltd\n");
    strcat(c, "This book is available in the library\n");
    strcat(c, "\n\n");
    strcat(c, "The Lord of the Rings: The Return of the King\n");
    strcat(c, "J. R. R. Tolkien\n");
    strcat(c, "ISBN: 9780007488353\n");
    strcat(c, "HarperCollins Publishers Ltd\n");
    strcat(c, "This book is available in the library\n");
    strcat(c, "\n\n");
    TEST_ASSERT_EQUAL_STRING_MESSAGE(c, list_books(0), "list book does not return correct string");
}

void test_create_student(){
    create_student("Placeholder", "Placeholder");
    Book book = {"The Lord of the Rings: The Fellowship of the Ring", "J. R. R. Tolkien", "9780007488315", "HarperCollins Publishers Ltd"};
    loan_book(&studentList[0], &book);
    TEST_ASSERT_EQUAL_STRING_MESSAGE("Placeholder", studentList[0].Username, "Username was not assigned correctly");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("Placeholder", studentList[0].Password, "Password was not assigned correctly");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("The Lord of the Rings: The Fellowship of the Ring", studentList[0].rentedBooks[0].Title, "The creation of the account does not let the account rent books");    
}

void test_overwrite_student(){
    
    TEST_ASSERT_FALSE_MESSAGE(create_student("Placeholder", "Placeholder2"), "create_student should return 0 if the student cannot be made");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("", studentList[1].Username, "student2 should not have been created with username");
    TEST_ASSERT_TRUE_MESSAGE(create_student("Placeholder2", "Placeholder"), "create_student should return 1 if the student can be made");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("Placeholder2", studentList[1].Username , "student2 should have been created with username");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("Placeholder", studentList[1].Password , "people are permitted to have the same password");
}

void test_delete_student_loaned_book(){
    Book book = {"The Lord of the Rings: The Fellowship of the Ring", "J. R. R. Tolkien", "9780007488315", "HarperCollins Publishers Ltd"};
    book.borrowed = true;
    book.isBorrowed.false.no = "Borrowed by: Placeholder";
    studentList[0].rentedBooks[0] = book;
    TEST_ASSERT_FALSE_MESSAGE(delete_student(studentList[0]), "delete_student should return 0 when the student cant be removed because they are borrowing a book");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("Placeholder", studentList[0].Username, "Student no longer has the right username, probably because it doesnt exist");
    
}

int main(void){
    UNITY_BEGIN();
    
    RUN_TEST(test_add_book);
    RUN_TEST(test_remove_book);
    RUN_TEST(test_loan_book);
    RUN_TEST(test_return_book);
    RUN_TEST(test_list_books);
    RUN_TEST(test_create_student);
    RUN_TEST(test_overwrite_student);
    RUN_TEST(test_delete_student_loaned_book);
    
    return UNITY_END();
}