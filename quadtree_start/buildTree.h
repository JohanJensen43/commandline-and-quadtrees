#ifndef BUILD__TREE__GUARD
#define BUILD__TREE__GUARD

Node *makeNode( double x, double y, int level );
void makeChildren( Node *parent );
void growTree(Node* node);

#endif