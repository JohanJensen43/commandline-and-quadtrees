#ifndef STUDENTSTRUCTURE__HEADER__GUARD
#define STUDENTSTRUCTURE__HEADER__GUARD
#include "bookStructure.h"

typedef struct {
    char Username[256];
    char Password[256];
    Book rentedBooks[10];
} StudentAccount;

#endif