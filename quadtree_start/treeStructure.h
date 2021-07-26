#ifndef TREE__STRUCTURE__GUARD
#define TREE__STRUCTURE__GUARD

struct qnode {
  int level;
  double xy[2];
  struct qnode *child[4];
};
typedef struct qnode Node;

#endif