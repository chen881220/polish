#ifndef _STACK_H_
#define _STACK_H_

#include "node.h"

void InitStack(Node **head);
void FreeStack(Node *head);
void Push(Node *head,Node *e);
void _Push(Node *head,Node e);
void Reverse(Node *head); 
void Display(Node *head);

Node Pop(Node *head);
Node *GetTop(Node *head);
bool IsEmpty(Node *head);

int Size(Node *head);

#endif
