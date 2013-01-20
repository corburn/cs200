/**
 * stack.c and stack.h copied from:
 * http://math.nist.gov/~RPozo/c++class/stack/stack.html
 */

#include <stdio.h>
#include "stack.h"

void push(Stack *S, int val)
{
    S->v[ S->top ] = val;
   (S->top)++;
/*  Equivalent to: S->v[ (S->top)++ ] = val;   */
}

int pop(Stack *S)
{
    (S->top)--;
    return (S->v[S->top]);
/*  Equivalent to: return (S->v[--(S->top)]);  */
}

void init(Stack *S)
{
    S->top = 0;
}

int isEmpty(Stack *S)
{
    return (S->top == 0);
}

void PrintStack(Stack *S)
{
    int i;
    if (S->top == 0)
       printf("Stack is empty.\n");
    else
    {
       printf("Stack contents: ");
       for (i=0;i<S->top;i++)
       {
          printf("%d  ",S->v[i]);
       }
       printf("\n");
    }
}