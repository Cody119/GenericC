#ifndef StackTemplate_h
#define StackTemplate_h

#define ST_FREE_SPACE 10
#define ST_GET_NAME(itemName, NAME) NAME##itemName
#define ST_CON_NAME(itemName, NAME) new_##NAME##itemName
#define ST_INIT_NAME(itemName, NAME) init_##NAME##itemName
#define ST_STACK_MAX_SIZE(stack) ((stack)->len)
#define ST_STACK_SIZE(stack) ((stack)->next)
#define ST_GET_ARRAY(stack) ((stack)->mainStack)
#define ST_STACK_INDEX(stack, index) (((stack)->mainStack)[index])
#define ST_STACK_WRAPPER_SIZE(NAME) sizeof(ST_GET_NAME(Stack, NAME))
//Dont thinks are acctually needed, but there a good reminder
//typedef void *(*allocator)(void*, size_t);
//typedef void *(*PANIC)(size_t, char*);

/* Generic template for LIFO arrays (stack), have functions that can do some other stuff 2
 * Its dependeds on stdlib.h
 * TODO: 
 * - Set size method that updates everything acoringly (may lose data, that is fine but the wrapper must be updated properly)
 * - Add a way to fix the size? not sure how that could be done efficently though
 * - Go through and make sure its still "generic", feel like it might not be anymore
 * - It hasnt really been tested much
*/


/* Start of header macro (function describtions in function macro) */
#define ST_STACK_HEADER(NAME, TYPE)																	\
/* The wrapper for the stack, holds all the details*/												\
typedef struct ST_GET_NAME(Stack, NAME) {															\
	TYPE* mainStack;																				\
	size_t len;																						\
	size_t next;																					\
} ST_GET_NAME(Stack, NAME);																			\
																									\
ST_GET_NAME(Stack, NAME)* ST_INIT_NAME(Stack, NAME)(ST_GET_NAME(Stack, NAME)* Stack, size_t size);	\
void ST_GET_NAME(IncSize, NAME)(ST_GET_NAME(Stack, NAME)* Stack, size_t size);						\
void ST_GET_NAME(Push, NAME)(ST_GET_NAME(Stack, NAME)* Stack, TYPE val);							\
TYPE ST_GET_NAME(Pop, NAME)(ST_GET_NAME(Stack, NAME)* Stack);										\
TYPE ST_GET_NAME(PopPos, NAME)(ST_GET_NAME(Stack, NAME)* Stack, int pos);							\
TYPE ST_GET_NAME(Read, NAME)(ST_GET_NAME(Stack, NAME)* Stack, int pos);								\
char ST_GET_NAME(Write, NAME)(ST_GET_NAME(Stack, NAME)* Stack, TYPE val, int pos);					\
void ST_GET_NAME(Clear, NAME)(ST_GET_NAME(Stack, NAME)* Stack);										\
void ST_GET_NAME(Free, NAME)(ST_GET_NAME(Stack, NAME)* Stack);										\
TYPE *ST_GET_NAME(ToArray, NAME)(ST_GET_NAME(Stack, NAME)* Stack);									\
void ST_GET_NAME(Shrink, NAME)(ST_GET_NAME(Stack, NAME)* Stack);									\

//This adds a bit more customisation
#define ST_STACK_CHEADER(NAME, TYPE, HEADER)														\
typedef struct ST_GET_NAME(Stack, NAME) {															\
	HEADER;																							\
	TYPE* mainStack;																				\
	size_t len;																						\
	size_t next;																					\
} ST_GET_NAME(Stack, NAME);																			\
																									\
ST_GET_NAME(Stack, NAME)* ST_INIT_NAME(Stack, NAME)(ST_GET_NAME(Stack, NAME)* Stack, size_t size);	\
void ST_GET_NAME(IncSize, NAME)(ST_GET_NAME(Stack, NAME)* Stack, size_t size);						\
void ST_GET_NAME(Push, NAME)(ST_GET_NAME(Stack, NAME)* Stack, TYPE val);							\
TYPE ST_GET_NAME(Pop, NAME)(ST_GET_NAME(Stack, NAME)* Stack);										\
TYPE ST_GET_NAME(PopPos, NAME)(ST_GET_NAME(Stack, NAME)* Stack, int pos);							\
TYPE ST_GET_NAME(Read, NAME)(ST_GET_NAME(Stack, NAME)* Stack, int pos);								\
char ST_GET_NAME(Write, NAME)(ST_GET_NAME(Stack, NAME)* Stack, TYPE val, int pos);					\
void ST_GET_NAME(Clear, NAME)(ST_GET_NAME(Stack, NAME)* Stack);										\
void ST_GET_NAME(Free, NAME)(ST_GET_NAME(Stack, NAME)* Stack);										\
TYPE *ST_GET_NAME(ToArray, NAME)(ST_GET_NAME(Stack, NAME)* Stack);									\
void ST_GET_NAME(Shrink, NAME)(ST_GET_NAME(Stack, NAME)* Stack);									\

/* This is used if and only if no header file is used 
 * (this can go in the .c source instead of using STACK_HEADER) 
*/
#define ST_STACK_TYPE(NAME, TYPE)																	\
typedef struct ST_GET_NAME(Stack, NAME) {															\
	TYPE* mainStack;																				\
	size_t len;																						\
	size_t next;																					\
} ST_GET_NAME(Stack, NAME);																			\

// Macro for getting a new stack, this allocates the wrapper with a specific allocator ALLOC
#define ST_NEW_STACK(NAME, ALLOC) (ST_INIT_NAME(Stack, NAME)((ST_GET_NAME(Stack, NAME)*) ALLOC(NULL, sizeof(ST_GET_NAME(Stack, NAME))), size))

/* Start of function def macro (includes function describtions) */
/* Args
 * NAME -> NAME of the stack, should be an alpha numeric string (shouldnt start with a number unless the NAME processor is modified)
 * TYPE -> type that the stack will hold, can be any struct of primitive type
 * ZERO -> the "ZERO" or 0 or defualt value of the passed struct/primitive
 * ALLOC -> a function/macro of type void *(*allocator)(void*, size_t) used to alloc memory, should work exact same as realloc (by c89 standared)
 * PANIC -> a function/macro of type void (*PANIC)(size_t, char*) called if an error occurs
*/
#define ST_DEFINE_STACK(NAME, TYPE, ZERO, ALLOC, PANIC)												\
																									\
/*Stack* initStack(Stack*, size_t) - initalise a new stack*/										\
/* called by new stack, allocates the stack memory and initalises all the variables */				\
/* doesnt allocate memory for the stack wrapper (that should be passed as the first arg) */			\
ST_GET_NAME(Stack, NAME)* ST_INIT_NAME(Stack, NAME)(ST_GET_NAME(Stack, NAME)* Stack, size_t size) {	\
	/*int startSize = (size == 0) ? DEFUALT_SIZE : size;*/											\
	ST_GET_ARRAY(Stack) = (size == 0) ? NULL : ALLOC(NULL, sizeof(TYPE) * size);					\
	Stack->len = size;																				\
	Stack->next = 0;																				\
	return Stack;																					\
}																									\
/*void IncSize(Stack*, size_t) - increments 		*/												\
/*the size of the stack by a specific number or		*/												\
/*the defualt free space is 0 is passed as teh size */ 												\
void ST_GET_NAME(IncSize, NAME)(ST_GET_NAME(Stack, NAME)* Stack, size_t size) {						\
	size_t newSize = size == 0 ? (Stack->len + ST_FREE_SPACE) : (Stack->len + size);				\
	ST_GET_ARRAY(Stack) = ALLOC(ST_GET_ARRAY(Stack), sizeof(TYPE) * newSize);						\
	Stack->len = newSize;																			\
}																									\
/*void Shrink(Stack*, size_t) -  		*/															\
void ST_GET_NAME(Shrink, NAME)(ST_GET_NAME(Stack, NAME)* Stack) {									\
	size_t newSize = Stack->next * sizeof(TYPE);													\
	ST_GET_ARRAY(Stack) = ALLOC(ST_GET_ARRAY(Stack), sizeof(TYPE) * newSize);						\
	Stack->len = newSize;																			\
}																									\
/*void Push(Stack*, TYPE) - pushes a value onto the top of the stack*/ 								\
void ST_GET_NAME(Push, NAME)(ST_GET_NAME(Stack, NAME)* Stack, TYPE val) {							\
	if (Stack->next == ST_STACK_MAX_SIZE(Stack))													\
		ST_GET_NAME(IncSize, NAME)(Stack, 0);														\
	ST_GET_ARRAY(Stack)[Stack->next] = val;															\
	Stack->next++;																					\
}																									\
/*char Write(Stack*, val, pos) - writes val to index pos*/											\
char ST_GET_NAME(Write, NAME)(ST_GET_NAME(Stack, NAME)* Stack, TYPE val, int pos) {					\
	if (pos < 0) pos = Stack->next + pos;															\
	if (pos < Stack->next  && pos >= 0) {															\
		ST_GET_ARRAY(Stack)[pos] = val;																\
		return 1;																					\
	}																								\
	PANIC(1, "index out of range");																	\
	return 0;																						\
}																									\
/*TYPE Pop(Stack*) - pop of the top of the stack    */												\
TYPE ST_GET_NAME(Pop, NAME)(ST_GET_NAME(Stack, NAME)* Stack) {										\
	if (Stack->next != 0) {																			\
		TYPE tmp = ST_GET_ARRAY(Stack)[Stack->next];												\
		/*ST_GET_ARRAY(Stack)[Stack->next] = ZERO;*/												\
		Stack->next--;																				\
		return tmp;																					\
	}																								\
	PANIC(1, "Stack underflow");																	\
	return ZERO;																					\
}																									\
/*TYPE PopPos(Stack*, int) - pop at pos (takes negatives, which work backward)*/					\
TYPE ST_GET_NAME(PopPos, NAME)(ST_GET_NAME(Stack, NAME)* Stack, int pos) {							\
	if (pos < 0) pos = Stack->next + pos;															\
	if (pos < Stack->next && pos >= 0) {															\
		TYPE tmp = ST_GET_ARRAY(Stack)[pos];														\
		int i = pos;																				\
		while (i + 1 != Stack->next) {																\
			ST_GET_ARRAY(Stack)[i] = ST_GET_ARRAY(Stack)[i + 1];									\
			i++;																					\
		}																							\
		Stack->next--;																				\
		return tmp;																					\
	}																								\
	PANIC(1, "index out of range");																	\
	return ZERO;																					\
}																									\
/*TYPE Read(Stack*, int) - return value at index pos*/												\
TYPE ST_GET_NAME(Read, NAME)(ST_GET_NAME(Stack, NAME)* Stack, int pos) {							\
	if (pos < 0) pos = Stack->next + pos;															\
	if (pos < Stack->next  && pos >= 0) {															\
		return ST_GET_ARRAY(Stack)[pos];															\
	}																								\
	PANIC(1, "index out of range");																	\
	return ZERO;																					\
}																									\
/*void Clear(Stack*) - clear the stack*/															\
/*Atm this isnt very efficent and kinda pointless, Stack->next = 0 would do the same thing*/		\
void ST_GET_NAME(Clear, NAME)(ST_GET_NAME(Stack, NAME)* Stack) {									\
	while (Stack->next != 0) {																		\
		ST_GET_NAME(Pop, NAME)(Stack);																\
	}																								\
}																									\
/*void Free(Stack*) - free the stack*/																\
void ST_GET_NAME(Free, NAME)(ST_GET_NAME(Stack, NAME)* Stack) {										\
	ALLOC(ST_GET_ARRAY(Stack), 0);																	\
	ALLOC(Stack, 0);																				\
}																									\
/* TYPE* ToArray(Stack*) - converts the stack to a normal array,                      */			\
/* freeing all stack specific memory (the stack will cease to exist					  */			\
TYPE *ST_GET_NAME(ToArray, NAME)(ST_GET_NAME(Stack, NAME)* Stack) {									\
	TYPE *tmp = ST_GET_ARRAY(Stack); 																\
	free(Stack);																					\
	return tmp;																						\
}																									\
/* size_t PushEmpty(Stack*) - push an empty stack frame  */											\
/* this moves the stack forawrd a slot, but dosent copy any data over */							\
/* note there is no garente the new stack frame will be empty*/										\
/* can be used with ST_GET_ARRAY as follows: &(ST_GET_ARRAY(Stack*)[PushEmpty(Stack*)]) */			\
/* above method will get a refrence to a new stack frame, can be more efficent */					\
size_t ST_GET_NAME(PushEmpty, NAME)(ST_GET_NAME(Stack, NAME)* Stack) {								\
	if (Stack->next == ST_STACK_MAX_SIZE(Stack))													\
		ST_GET_NAME(IncSize, NAME)(Stack, 0);														\
	return Stack->next++;																			\
}																									\

#endif