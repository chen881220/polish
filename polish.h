#ifndef _POLISH_H_
#define _POLISH_H_

#include "node.h"

void Parse_Expr(Node *n,const char *expr);
void Mid_To_Rev(Node *mid,Node *rev);
double Calc_By_Rev(Node *rev);
double Calc_By_Mid(Node *mid);
static void Calc_Mid_Bracket(Node *mid,Node *ret);
static double __Calc_By_Mid(Node *mid);
static double Calc_By_Stack(Node *head);

#endif
