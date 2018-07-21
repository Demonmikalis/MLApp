#include "Expression.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


static char Precede2(char a, char b){
    int i,j;
    char pre[][8]={         
        /*make a table for operate pirority*/
        {'>','>','<','<','<','<','>','>'},
        {'>','>','<','<','<','<','>','>'},
        {'>','>','>','>','<','<','>','>'},
        {'>','>','>','>','<','<','>','>'},
        {'>','>','>','>','>','<','>','>'},
        {'<','<','<','<','<','<','=','0'},
        {'>','>','>','>','>','0','>','>'},
        {'<','<','<','<','<','<','0','='}};
    switch(a){
        case '+': i=0; break;
        case '-': i=1; break;
        case '*': i=2; break;
        case '/': i=3; break;
        case '^': i=4; break;
        case '(': i=5; break;
        case ')': i=6; break;
        case ';': i=7; break;
    }
    switch(b){
        case '+': j=0; break;
        case '-': j=1; break;
        case '*': j=2; break;
        case '/': j=3; break;
        case '^': j=4; break;
        case '(': j=5; break;
        case ')': j=6; break;
        case ';': j=7; break;
    }
    return pre[i][j];
}

static char Precede(char a, char b){
    int i,j;
    char pre[][7]={         
        /*make a table for operate pirority*/
        {'>','>','<','<','<','>','>'},
        {'>','>','<','<','<','>','>'},
        {'>','>','>','>','<','>','>'},
        {'>','>','>','>','<','>','>'},
        {'<','<','<','<','<','=','0'},
        {'>','>','>','>','0','>','>'},
        {'<','<','<','<','<','0','='}};
    switch(a){
        case '+': i=0; break;
        case '-': i=1; break;
        case '*': i=2; break;
        case '/': i=3; break;
        case '(': i=4; break;
        case ')': i=5; break;
        case '#': i=6; break;
    }
    switch(b){
        case '+': j=0; break;
        case '-': j=1; break;
        case '*': j=2; break;
        case '/': j=3; break;
        case '(': j=4; break;
        case ')': j=5; break;
        case '#': j=6; break;
    }
    return pre[i][j];
}

static double Operate(double a, char theta, double b){
    double i,j,result;
    i=a;
    j=b;

    switch(theta)   {
        case '+': result = i + j; break;
        case '-': result = i - j; break;
        case '*': result = i * j; break;
        case '/': result = i / j; break;
        case '^': result = pow(i,j);break;
    }
    return result;
}

static int in(char c,char op[]){
    char *p;
    p=op;
    while(*p != '\0'){
        if(c == *p)
            return TRUE;
        p++;
    }
    return FALSE;
}


static int getNext(char str[], double *n, int *cnt){
    int counter = *cnt;
    //if(*cnt>strlen(str)) return FALSE;
    char *c;
    *n=0;
    c = str + *cnt;
    while(*c ==' '){c++;counter++;}; 
    //printf("%s\n",c);
    if(!isdigit(*c)){            
        *n=*c;
        *cnt=counter+1;
        return TRUE;
    }
    
    do{                        
        *n=*n*10+(*c-'0');      
        c++;
        counter++;
    }while(isdigit(*c));
    
    //check whether float point occurs
    if(*c == '.')
    {
        
    }

    *cnt = counter;          
    return FALSE;
}


double EvaluateExpression(char exp[])
{
    int offset = 0;

    int flag;
    double c;
    int x,theta;
    double a,b;
    // store operator char
    Stack *OPTR = (Stack*) malloc(sizeof(struct Stack));
    // store double number
    Stack *OPND = (Stack*) malloc(sizeof(struct Stack));
    int sz_OPTR=0, sz_OPND=0;
        
    //Push(&OPTR,'#');
    char sharp = ';';
    StackPush(&OPTR,&sharp,&sz_OPTR);
    flag=getNext(exp, &c, &offset);
    //GetTop(OPTR, &x);	
    x = *(char *)StackTop(OPTR);

    int *c_temp;
    
    while(((int)c!=';' || x != ';'))
    {
        if(flag == FALSE)
        {   
            double *c_temp2 = (double*)malloc(sizeof(double));
            *c_temp2 = c;
            StackPush(&OPND,c_temp2,&sz_OPND);
            flag = getNext(exp,&c,&offset);
        }
        else
        {
            //GetTop(OPTR, &x);
            x = *(char *)StackTop(OPTR);
            //printf("x = %c and c=%c\n",x,(int)c);
            switch(Precede2(x, (int)c))
            {
                
                case '<'://top elem has the low pirority
                    c_temp = (int*)malloc(sizeof(int));
                    *c_temp = c;
                    StackPush(&OPTR,c_temp,&sz_OPTR);
                    flag = getNext(exp,&c,&offset);
                    break;
                case '='://get rid of () and accept next elem
                    //printf("here =\n"); 
                    x = *(char*)StackPop(&OPTR,&sz_OPTR);
                    flag = getNext(exp,&c,&offset);
                    break;
                case '>':// operate
                    //printf("here >\n"); 
                    theta = *(char*)StackPop(&OPTR, &sz_OPTR);
                    b = *(double*)StackPop(&OPND,&sz_OPND);
                    a = *(double*)StackPop(&OPND,&sz_OPND);
                    double tmp = Operate(a, theta, b);
                    double *c_temp2 = (double*)malloc(sizeof(double));
                    *c_temp2 = tmp;
                    StackPush(&OPND,c_temp2,&sz_OPND);
                    break;
            }
        }
        //GetTop(OPTR, &x);
        x = *(char *)StackTop(OPTR);
    
    }

    //GetTop(OPND, &c);
    c = *(double*)StackTop(OPND);
    printf("ans=%f\n",c);
    printf("sz_OPTR=%d and sz_OPND=%d\n",sz_OPTR,sz_OPND);
    StackFree(&OPTR,sz_OPTR);
    StackFree(&OPND,sz_OPND);
    free(OPTR);
    free(OPND);
    return c;

}
