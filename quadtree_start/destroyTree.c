#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "treeStructure.h"
#include "writeTree.h"
#include "buildTree.h"

void destroyTree(Node* node){
    //if the node has children
    if(node->child[0] != NULL){
        //recursively call every child it has, and afterwards set the children to NULL
        for(int i = 0; i < 4; ++i){
            destroyTree(node->child[i]);
            node->child[i]=NULL;
        }
        //free the head node
        free(node);
        return;
    } else {
        //if the node doesnt have any children just free the node
        free(node);
        return;
    }
}