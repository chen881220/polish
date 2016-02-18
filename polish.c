#include "polish.h"
#include "node.h"
#include "stack.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

#define ISOPT(x) ((x)=='+'||(x)=='-'||(x)=='*'||(x)=='/')

void Parse_Expr(Node *n,const char *expr)
{
    int ii,count;
	for( ii=0,count=0; expr[ii]!='\0'; ++ii )
	{
		if( expr[ii]=='.' || isdigit(expr[ii]) )
		{
			++count;
		}
		else if( expr[ii]=='(' )
		{
			Push(n,CreateNode(expr[ii],L));
		}
		else
		{
			if( count!=0 )
			{
				char *buf = (char *)malloc(sizeof(count+1));
				memset(buf,0,count+1);
				memcpy((void*)buf,(void*)(&expr[ii-count]),count);
				Push(n,CreateNode(atof(buf),NUM));
				count=0;
				free(buf);
			}

			if( ISOPT(expr[ii]) )
				Push(n,CreateNode(expr[ii],OPT)); 

			if( expr[ii]==')' )
				Push(n,CreateNode(expr[ii],R));
		}
	}

    if( count!=0 )
    {
		char *buf = (char *)malloc(sizeof(count+1));
		memset(buf,0,count+1);
        memcpy((void*)buf,(void*)(&expr[strlen(expr)-count]),count);
        Push(n,CreateNode(atof(buf),NUM));
		free(buf);
    }
}

void Mid_To_Rev(Node *mid,Node *rev)
{
    Node *tmp = NULL;
    InitStack(&tmp);

    while( !IsEmpty(mid) )
    {
        Node n = Pop(mid);
        if( n._type==L )
        {
            _Push(tmp,n);
        }
        else if( n._type==R )
        {
            Node top = Pop(tmp);
            while( top._type != L )
            {
                _Push(rev,top);
                top = Pop(tmp);
            }
        }
        else if( IsOpt(&n) )
        {
            int cur_level = OptLevel(&n);
            int top_level = OptLevel(GetTop(tmp));

            while( top_level >= cur_level )
            {
                _Push(rev,Pop(tmp));
                top_level = OptLevel(GetTop(tmp));
            }

            _Push(tmp,n);
        }
        else
        {
            _Push(rev,n);
        }
    }

    while( !IsEmpty(tmp) )
    {
        _Push(rev,Pop(tmp));
    }

    FreeStack(tmp);
}

double Calc_By_Rev(Node *rev)
{
    Node *tmp = NULL;
    InitStack(&tmp);

    while( !IsEmpty(rev) )
    {
        Node top = Pop(rev);

        if( IsOpt(&top) )
        {
            Node d2 = Pop(tmp);
            Node d1 = Pop(tmp);
            double res = 0.0;

            switch( (char)top.elem )
            {
            case '+':
                res=d1.elem+d2.elem;
                break;
            case '-':
                res=d1.elem-d2.elem;
                break;
            case '*':
                res=d1.elem*d2.elem;
                break;
            case '/':
                res=d1.elem/d2.elem;
                break;
            }

            Node *pRes = (Node*)malloc(sizeof(Node));
            pRes->elem = res;
            pRes->_type = NUM;
            Push(tmp,pRes);
        }
        else
        {
            _Push(tmp,top);
        }
    }

    double res = tmp->pNext->elem; 
    FreeStack(tmp);

    return res;
}

double Calc_By_Mid(Node *mid)
{
	Node *ret = NULL;
	InitStack(&ret);
	
	Calc_Mid_Bracket(mid,ret);
	Reverse(ret);
	
	double res = __Calc_By_Mid(ret);
	FreeStack(ret);
	
	return res;
}

static void Calc_Mid_Bracket(Node *head,Node *ret)
{
    Node *buf = NULL;
    InitStack(&buf);

    while( !IsEmpty(head) )
    {
        Node top = Pop(head);
        if( top._type == L )
        {
            Calc_Mid_Bracket(head,buf);

            Reverse(buf);
            Node *n = (Node*)malloc(sizeof(Node));
            n->elem = __Calc_By_Mid(buf);
            n->_type = NUM;
            Push(ret,n);
        }       
        else if( top._type == R )
        {
            return ;
        }
        else
        {
            _Push(ret,top);
        }
    }
}

static double __Calc_By_Mid(Node *mid)
{
    Node *num = NULL;
    Node *opt = NULL;
    InitStack(&num);
    InitStack(&opt);

    while( !IsEmpty(mid) )
    {
        Node n = Pop(mid);
        if( n._type==NUM )
        {
            _Push(num,n);        
        }
        else
        {
            int top_level = OptLevel(GetTop(opt));
            int cur_level = OptLevel(&n);
                   
            Node *tmp = NULL;
            while( cur_level <= top_level )
            {
                InitStack(&tmp);
                _Push(tmp,Pop(num));
                _Push(tmp,Pop(opt));
                _Push(tmp,Pop(num));

                Push(num,CreateNode(Calc_By_Stack(tmp),NUM));

                top_level = OptLevel(GetTop(opt));
                FreeStack(tmp);
            }

            _Push(opt,n);
        }
    }

    Node *tmp = NULL;
    while( !IsEmpty(opt) )
    {
        InitStack(&tmp);

        _Push(tmp,Pop(num));
        _Push(tmp,Pop(opt));
        _Push(tmp,Pop(num));


        Node *pRes = (Node*)malloc(sizeof(Node));
        pRes->elem = Calc_By_Stack(tmp);
        pRes->_type = NUM;
        Push(num,pRes);
    }
    double res = GetTop(num)->elem;

    FreeStack(num);
    FreeStack(opt);
    FreeStack(tmp);

    return res;
}

static double Calc_By_Stack(Node *head)
{
    double sum = Pop(head).elem;

    while( !IsEmpty(head) )
    {
        Node opt = Pop(head);
        Node n2 = Pop(head);

        switch( (char)opt.elem )
        {
        case '+':
            sum = sum+n2.elem;
            break;
        case '-':
            sum = sum-n2.elem;
            break;
        case '*':
            sum = sum*n2.elem;
            break;
        case '/':
            sum = sum/n2.elem;
            break;
        }
    }

    return sum;
}
