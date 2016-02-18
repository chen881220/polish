#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "calc.h"

int main()
{
	char *s[] = {
		"(4.1+3.091-4.0/8.11*0.1)*2+3-1-1+6-2*3+1",
		"43+2.231/(4.1+3.091-4.0/8.11*0.1)*2+3-1-1+6-2*3+1",
		"43+2.231/4.1+3.091-4.0/8.11*0.1*2+3-1-1+6-2*3+1",
		"(5+(1+2))*3+4",
		"3-2-1",
		"1+((2+3)+4)+5",
		"1+(2+((1+2*3+4)*2+5))+6"
	};

    int ii;
    for( ii=0; ii<sizeof(s)/sizeof(s[0]); ++ii )
    {
        printf("%f\t",Calc_Rev_Polish(s[ii]));
        printf("%f\n",Calc_Mid_Polish(s[ii]));
    }

    return 0;
}
