#ifndef _NODE_H_
#define _NODE_H_

#include <stdbool.h>

typedef enum _Type
{
    NUM=1,          // number
    OPT,            // + - * / 
    L,              // (
    R,              // )
    N,              // NULL
}TYPE;

typedef struct _Node
{
    double elem;
    struct _Node *pNext;
    TYPE _type;
}Node;

void ZeroNode(Node *n);
void PrintNode(Node *n);
bool IsOpt(Node *n);
unsigned int OptLevel(Node *n);
Node CopyNode(Node *n);
Node *CreateNode(double e,TYPE t);

#endif
