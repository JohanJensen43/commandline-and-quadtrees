#ifndef BOOKSTRUCTURE__HEADER__GUARD
#define BOOKSTRUCTURE__HEADER__GUARD
enum boolean {false = 0, true = 1};


typedef struct {
    char Title[256];
    char Author[256];
    char ISBN[256];
    char Publisher[256];
    enum boolean borrowed;
    union{
        struct{
            char *no;
        } false;
        struct{
            char *yes;
        } true;
    }isBorrowed;
} Book;

#endif