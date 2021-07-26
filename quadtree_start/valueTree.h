#ifndef VALUE__TREE__STRUCTURE__GUARD
#define VALUE__TREE__STRUCTURE__GUARD
#include "stdbool.h"

double dataFunction( double x, double y, int choice );

bool indicator( Node *node, double tolerance, int choice );

void visitAndAdd(Node* node);
#endif