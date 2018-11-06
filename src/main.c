
#include <stdio.h>


#define NAME int
#define TYPE int
#define ZERO 0
#define PANIC(x, y) printf("%s\n", y)
#include "GStack/StackGeneric.h"
#include "GStack/EndStackDec.h"


void main() {
    int_stack stack;
    int mem[20];

    init_int_stack(&stack, 20, mem);
    int_push(&stack, 56);
    int_push(&stack, 27);
    int_push(&stack, 37);

    int_remove(&stack, -4);

    int a = int_pop(&stack);
    int b = int_pop(&stack);
    printf("%d %d\n", a, b);

}