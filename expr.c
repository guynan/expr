/* expr: evaluates a reverse Polish Expression */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define STACK_HEIGHT    100
int stackc = 0; /* global stack counter */


int calculate (int op1, int op2, char operator);
int main(int argc, char **argv);
void push(int c, int *stack);
int strtoint(char *arr);
int isSign(char *arg);
int pop(int *stack);
int len(char *arr);


int main(int argc, char **argv)
{
        /* If we aren't passing in enough values */
        if(argc == 1){
                printf("Usage: expr [postfix expression]\n");
                return 1;
        }

        int i, res, op1, op2;

        /* Initialising an array to become our stack */
        int *stack = calloc(STACK_HEIGHT, sizeof(int));

        for (int c = 1 ; c < argc; c++){
                if(isSign(argv[c])){
                        op2 = pop(stack);
                        op1 = pop(stack);

                        /* Dereference here is kinda safe because we
                         * check in the isSign() function */
                        res = calculate(op1, op2, *argv[c]); 
                        push(res, stack);

                } else {

                        i = strtoint(argv[c]);
                        push(i, stack);
                }
        }

        printf("%d\n", stack[stackc]);

        return 0;

}

/* Push a character onto the top of
 * the stack and increment stack counter */
void push(int c, int *stack)
{
        /* Problem here is the first push... 
         * ie when stackc == 0 */
        stack[++stackc] = c;
}


/* Passing in the reference to the stack 
 * resets the top value and returns the
 * value of the top of the stack */
int pop(int *stack)
{
        /* Speed up: Have a stack pointer that points 
         * to the top of the stack */
        int res = stack[stackc--]; 
        return res;
}


int isSign(char *arg)
{
        if(len(arg) != 1) return 0;

        int i = (int) *arg;

        return (i == '+' || i == '-' || 
                i == '/' || i == '*' ||
                i == '^'
                );
}


int calculate (int op1, int op2, char operator)
{
        switch((int) operator){
                case '+' : return (op1 + op2);
                case '-' : return (op1 - op2);
                case '*' : return (op1 * op2);
                case '/' : return (op1 / op2);
                case '^' : return pow(op1, op2);
                default  : return 0;
        }

}


int len(char *arr)
{
        int i = 0;

        for( ; *arr++; i++);

        return i;
}


int strtoint(char *arr)    
{
        int dec = 0;

        for( ; *arr != '\0'; dec = dec * 10 + (*arr++ - '0'))
                ;

        return dec;
}


