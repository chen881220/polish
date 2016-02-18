#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

void InitStack(Node **head)
{
    *head = (Node *)malloc(sizeof(Node));
    ZeroNode(*head);
}

void FreeStack(Node *head)
{
    Node *pFree = head->pNext;
    Node *pBuf = NULL;

    while( pFree != NULL )
    {
       pBuf = pFree->pNext;
       free(pFree);
       pFree = pBuf;
    }

    free(head);
}

void Push(Node *head,Node *e)
{
    e->pNext = head->pNext;
    head->pNext = e;
}

void _Push(Node *head,Node e)
{
    Node *n = (Node*)malloc(sizeof(Node));
    n->elem = e.elem;
    n->_type = e._type;

    n->pNext = head->pNext;
    head->pNext = n;
}

void Reverse(Node *head)
{
    if( IsEmpty(head) )
        return ;

    Node *cur = head->pNext;
    Node *next = NULL;
    Node *pre = NULL;

    while( cur!=NULL )
    {
        next = cur->pNext;
        cur->pNext = pre;
        pre = cur;
        cur = next;
    }

    head->pNext = pre;
}

void Display(Node *head)
{
    Node *pBuf = head->pNext;
    while( pBuf != NULL )
    {
        PrintNode(pBuf);
        pBuf = pBuf->pNext;
    }
    printf("\n");
}

Node Pop(Node *head)
{
    Node n;
    ZeroNode(&n);

    if( IsEmpty(head) )
        return n;

    Node *pBuf = head->pNext;
    head->pNext = pBuf->pNext;

    n = CopyNode(pBuf);
    free(pBuf);

    return n;
}

Node *GetTop(Node *head)
{
    if( IsEmpty(head) )
        return NULL;
    return head->pNext;
}

bool IsEmpty(Node *head)
{
    return head->pNext==NULL?true:false;
}

int Size(Node *head)
{
    Node *p = NULL;
    int count=0;
    for( p=head->pNext; p!=NULL; p=p->pNext )
        ++count;

    return count;
}
