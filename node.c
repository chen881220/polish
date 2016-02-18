#include "node.h"
#include <stdio.h> 
#include <stdlib.h>

#define NUM ((char)1)
#define OPT ((char)2)
#define L   ((char)3)
#define R   ((char)4)
#define N   ((char)5)

void ZeroNode(Node *n)
{
    n->elem = 0.0;
    n->pNext = NULL;
    n->_type = N;
}

void PrintNode(Node *n)
{
	if( n->_type==NUM )
		printf("{%f}\n",n->elem);
	else
		printf("{%c}\n",(char)n->elem);
}

bool IsOpt(Node *n)
{
    if( n==NULL || n->_type!=OPT )
        return false;

    return true;
}

unsigned int OptLevel(Node *n)
{
    if( n==NULL )
        return 0;

    char opt = (char)(n->elem);
    if( opt=='+' || opt=='-' )
        return 1;
    if( opt=='*' || opt=='/' )
        return 2;
    return 0;
}

Node CopyNode(Node *n)
{
    Node node;
    node.elem = n->elem;
    node.pNext = NULL;
    node._type = n->_type;

    return node;
}

Node *CreateNode(double e,TYPE t)
{
    Node *n = (Node*)malloc(sizeof(Node));
    n->elem = e;
    n->_type = t;
    return n;
}
