
/* Polex: evaluates a reverse Polish Expression 
 * it accepts operations of addition, subtraction, 
 * multiplication, exponentiation and integer 
 * division. It evaluates in 64 bits and has a 
 * stack size of 100 elements which is more than 
 * enough to get by with. This was a fun afternoon
 * exercise because I like reverse Polish notation 
 *
 * Guy Nankivell */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>


#define STACK_HEIGHT    100 /* This is very generous */


int64_t calculate(int64_t op1, int64_t op2, char operator); 
void push(int64_t c, int64_t** stp);
int main(int argc, char** argv);
int64_t strtoint(char* arr);
int64_t pop(int64_t** stp);
int isSign(char* arg);
int len(char* arr);


int main(int argc, char **argv)
{
        /* If we aren't passing in enough values */
        if(argc == 1){
                printf("Usage: polex [postfix expression]\n");
                return 1;
        }

        int64_t i, res, op1, op2;

        /* Initialising an array to become our stack */
        int64_t *stack = calloc(STACK_HEIGHT, sizeof(int64_t));

        /* Our stack pointer to speed up pop/peek operations */ 
        int64_t *sptr = &stack[0];

        for ( ; *argv; argv++){
                if(isSign(*argv)){
                        op2 = pop(&sptr);
                        op1 = pop(&sptr);

                        /* Dereference here is kinda safe because we
                         * check in the isSign() function */
                        res = calculate(op1, op2, **argv); 
                        push(res, &sptr);

                } else {

                        i = strtoint(*argv);
                        push(i, &sptr);
                }
        }

        printf("%" PRId64 "\n", *sptr); 

        return 0;

}

/* Push a character onto the top of
 * the stack and increment the stack pointer */
void push(int64_t c, int64_t**  sptr)
{
        /* Problem here is the first push... 
         * ie when stackc == 0 */
        ++(*sptr);
        **sptr = c;
}


/* Passing in the reference to the stack,
 * decrements the stack pointer and returns the
 * value of the top of the stack */
int64_t pop(int64_t** sptr)
{
        int64_t val = **sptr;
        (*sptr)--;

        return val;
}


int isSign(char* arg)
{
        if(len(arg) != 1) return 0;

        int i = (int) *arg;

        return (i == '+' || i == '-' || 
                i == '/' || i == '*' ||
                i == '^'
                );
}


int64_t calculate (int64_t op1, int64_t op2, char operator)
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


/* Simply returns the length of a char array */
int len(char* arr)
{
        int i = 0;

        for( ; *arr++; i++);

        return i;
}


int64_t strtoint(char* arr)    
{
        int64_t dec = 0;

        for( ; *arr != '\0'; dec = dec * 10 + (*arr++ - '0'))
                ;

        return dec;
}

