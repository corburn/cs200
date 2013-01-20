/**
 * stack.c and stack.h copied from:
 * http://math.nist.gov/~RPozo/c++class/stack/stack.html
 *
 * stack.h -- Stack declaration and function prototypes:
 */

typedef struct
{
    int v[20];
    int top;
} Stack;

void push(Stack *S, int val);
int pop(Stack *S);
void init(Stack *S);
int isEmpty(Stack *S);
void PrintStack(Stack *S);
