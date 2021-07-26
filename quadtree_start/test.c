#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "treeStructure.h"
#include "writeTree.h"
#include "buildTree.h"
#include "destroyTree.h"
#include "valueTree.h"
#include "stdbool.h"
#include "valueTree.h"

void level2(Node* node);
void nonUniformLevel3(Node* node);

void task1(){
    //level 2 tree
    Node *head;
    head = makeNode( 0.0,0.0, 0 );
    level2(head);
    destroyTree(head);
    
    //non uniform level 3 tree
    Node *node;
    node = makeNode( 0.0,0.0, 0 );
    nonUniformLevel3(node);
    writeTree(node);
    destroyTree(node);
}

void task2(){
    //level 2 tree
    Node *head;
    head = makeNode( 0.0,0.0, 0 );
    level2(head);
    
    //grow it
    growTree(head);
    destroyTree(head);
    
    //non uniform level 3 tree
    Node *node;
    node = makeNode( 0.0,0.0, 0 );
    nonUniformLevel3(node);
    
    //grow it
    growTree(node);
    writeTree(node);
    destroyTree(node);
}

void task3(){
    Node *node;
    node = makeNode( 0.0,0.0, 0 );
    nonUniformLevel3(node);
    growTree(node);
    growTree(node);
    growTree(node);
    growTree(node);
    growTree(node);
    growTree(node);
    growTree(node);
    growTree(node);
    writeTree(node);
    destroyTree(node);
}

void task4(){
    Node *node;
    node = makeNode( 0.0,0.0, 0 );
    level2(node);
    visitAndAdd(node);
    writeTree(node);
    destroyTree(node);
}

void level2(Node* node){
    growTree(node);
    growTree(node);
}

void nonUniformLevel3(Node* node){
    makeChildren(node);
    makeChildren( node->child[0] );
    makeChildren( node->child[2] );
    makeChildren( node->child[3] );
    growTree(node);
}


int main( int argc, char **argv ) {

  task1();
  task2();
  task3();
  task4();

  return 0;
}