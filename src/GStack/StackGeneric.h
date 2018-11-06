/*
    HEADER
    NAME, 
    TYPE, 
    ZERO, 
    PANIC
*/


#include "GStackVarCheck.h"
#include "Generics.h"

#define S_N G_GET_NAME(stack, NAME)

typedef struct S_N {
    HEADER;
    TYPE* mem;
    unsigned int len;
    TYPE* next;
} S_N;

S_N *G_INIT_NAME(stack, NAME)(S_N *stack, unsigned int len, TYPE *mem) {
    stack->len = len;
    stack->next = stack->mem = mem;
    return stack;
}

#ifdef ALLOC
//Resize function
#endif

/*void Push(Stack*, TYPE) - pushes a value onto the top of the stack*/
void G_GET_NAME(push, NAME)(S_N* stack, TYPE val) {
#ifdef ALLOC

#else
#ifdef PANIC
    if (stack->next - stack->mem == stack->len - 1) {
		PANIC(1, "Stack overflow");
		return;
    }
#endif
#endif
    *(stack->next++) = val;
}

/*TYPE Pop(Stack*) - pop of the top of the stack    */
TYPE G_GET_NAME(pop, NAME)(S_N* stack) {
#ifdef PANIC
    if (stack->next == stack->mem - 1) {
		PANIC(1, "Stack underflow");
		return ZERO;
    }
#endif
    return *(--stack->next);
}

/*TYPE PopPos(Stack*, int) - pop at pos (takes negatives, which work backward)*/
TYPE G_GET_NAME(remove, NAME)(S_N* stack, int pos) {

    TYPE *r_pos = pos < 0 ? stack->next + pos : stack->mem + pos;
    TYPE ret = *r_pos;
#ifdef PANIC
    if (stack->mem > r_pos || stack->next <= r_pos) {
        PANIC(1, "index out of range");
        return ZERO;
    }
#endif
    TYPE *next = r_pos + 1;
    while (next != stack->next) {
        *r_pos = *next;
        r_pos++;
        next++;
    }

    stack->next--;
    return ret;
}
/*TYPE set(Stack*, int) - return value at index pos*/
TYPE G_GET_NAME(get, NAME)(S_N* stack, int pos) {
    TYPE *r_pos = pos < 0 ? stack->next + pos : stack->mem + pos;
#ifdef PANIC
    if (stack->mem > r_pos || stack->next <= r_pos) {
        PANIC(1, "index out of range");
        return ZERO;
    }
#endif
    return *r_pos;
}

/*TYPE set(Stack*, int) - return value at index pos*/
void G_GET_NAME(set, NAME)(S_N* stack, int pos, TYPE val) {
    TYPE *r_pos = pos < 0 ? stack->next + pos : stack->mem + pos;
#ifdef PANIC
    if (stack->mem > r_pos || stack->next <= r_pos) {
        PANIC(1, "index out of range");
        return;
    }
#endif
    *r_pos = val;
}

#undef S_N

