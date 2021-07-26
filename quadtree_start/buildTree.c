#include "treeStructure.h"
#include "buildTree.h"
#include "stdio.h"
#include "math.h"
#include "stdlib.h"
#define MAX_TREE_LEVEL 7

Node *makeNode( double x, double y, int level ) {
  int i;

  Node *node = (Node *)malloc(sizeof(Node));

  node->level = level;

  node->xy[0] = x;
  node->xy[1] = y;

  for( i=0;i<4;++i )
    node->child[i] = NULL;

  return node;
}

// split a leaf nodes into 4 children

void makeChildren( Node *parent ) {
  if (parent->level >= MAX_TREE_LEVEL){
    return;
  }
  
  double x = parent->xy[0];
  double y = parent->xy[1];

  int level = parent->level;

  double hChild = pow(2.0,-(level+1));

  parent->child[0] = makeNode( x,y, level+1 );
  parent->child[1] = makeNode( x+hChild,y, level+1 );
  parent->child[2] = makeNode( x+hChild,y+hChild, level+1 );
  parent->child[3] = makeNode( x,y+hChild, level+1 );

  return;
}

void growTree(Node* node){
    //if the node already has children go down to its children instead
    if(node->child[0] != NULL){
        for (int i = 0; i < 4; ++i){
            growTree(node->child[i]);
        }
    //otherwise make some children for the node
    } else {
        makeChildren(node);
    }
    
}