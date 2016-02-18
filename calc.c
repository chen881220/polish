#include "polish.h"
#include "node.h"
#include <stdio.h>

double Calc_Mid_Polish(const char *expr)
{
    Node *mid = NULL;
    InitStack(&mid);

    Parse_Expr(mid,expr);
    Reverse(mid);

	double res = Calc_By_Mid(mid);
	FreeStack(mid);

    return res;
}

double Calc_Rev_Polish(const char *expr)
{
    Node *mid = NULL;
    Node *rev = NULL;

    InitStack(&mid);
    InitStack(&rev);

    Parse_Expr(mid,expr);
    Reverse(mid);

    Mid_To_Rev(mid,rev);
    Reverse(rev);

    double res = Calc_By_Rev(rev);
    FreeStack(mid);
    FreeStack(rev);

    return res;
}
