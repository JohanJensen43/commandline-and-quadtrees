#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "treeStructure.h"
#include "writeTree.h"
#include "buildTree.h"
#include "destroyTree.h"
#include "test.h"
#include "valueTree.h"
#include "stdbool.h"


int main( int argc, char **argv ) {

  Node *head;

  // make the head node
  head = makeNode( 0.0,0.0, 0 );

  //task1();
  //task2();
  //task3();
  //task4();  
  
  // make a tree
  makeChildren( head );
  makeChildren( head->child[0] );
  makeChildren( head->child[1] );
  makeChildren( head->child[2] );
  makeChildren( head->child[3] );  
  
  // print the tree for Gnuplot
  writeTree( head );
  
  destroyTree(head);

  return 0;
}