#pragma once 

#include <stdio.h>
#include <stdlib.h>

typedef double data_stack; /// defined as double but you can override it 

#define STACK_UNDERFLOW -1
#define STACK_OVERFLOW -2
#define STACK_NOT_EXIST -3
#define STACK_TYPE_ERR -4
#define STACK_LACK_OF_MEMORY -5
#define STACK_BAD_ARGS -6
#define STACK_UNNOWN_ERROR -10

#define MEM_SHOP "http://newegg.com"

#define STACK_GOOD 1
#define STACK_BROKEN 0

#define MAX_BUFF 10000000
#define STACK_MAX_CAPCITY ( MAX_BUFF / sizeof(data_stack) )

struct Stack
{
	data_stack *data;
	size_t size = 0;
	size_t capacity = 0;
	int stack_state = STACK_NOT_EXIST;
};

/**
 /brief construct a Stack using dimamic memory

 /param[in] size_of_init size of stack initializing // default is 0

 /return pointer to created Stack
*/
Stack* StackCtorDin(size_t size_to_init = 0) /// to-do assert and err mesaging
{
	Stack *stack = (Stack*)calloc(1, sizeof(Stack));
	stack->data = (data_stack*)calloc(size_to_init, sizeof(data_stack));
	stack->capacity = size_to_init;
	stack->size = size_to_init;
	stack->stack_state = STACK_GOOD;
	return stack;
}

/**
 /brief construct a Stack

 /param[in] stack stack to construct
 /param[in] size_of_init size of stack initializing // default is 0

 /return size of output_data or error messege
*/
int StackCtor(Stack* stack, size_t size_to_init = 0) /// to-do assert and err mesaging
{
	stack->data = (data_stack*)calloc(size_to_init, sizeof(data_stack));
	stack->capacity = size_to_init;
	stack->size = size_to_init;
	stack->stack_state = STACK_GOOD;
	return size_to_init;
}

/**
 /brief destruct a Stack

 /param[in] stack stack to destruct

 /return size of destructed or error messege
*/
int StackDtor(Stack* stack) /// to-do assert and err mesaging
{
	size_t stack_size = stack->size;
	free(stack->data);
	return stack_size;
}

/**
 /brief destruct a Stack dinamic

 /param[in] stack stack to destruct dinamic

 /return size of destructed or error messege
*/
int StackDtorDin(Stack* stack) /// to-do assert and err mesaging
{
	size_t stack_size = stack->size;
	free(stack->data);
	free(stack);
	return stack_size;
}

int StackClean(Stack* stack)
{

}

int StackFree(Stack* stack)
{

}

int StackPush(Stack* stack)
{

}

int StackOk(Stack* stack)
{

}

void StackDump(Stack* stack)
{

}

int StackMemAlloc(size_t amount)
{
	return int(amount);
}
int StackResize(Stack* stack)
{

}
int StackSrink_to_fit(Stack* stack)
{

}
/* unmaked
size_t StackMaxCapacity(Stack* stack)
{
	return 0;
}
*/

int StackPush(Stack* stack)
{

}

data_stack StackPop(Stack* stack)
{

}

data_stack StackFront(Stack* stack)
{

}
/**
 /brief get all data from Stack

 /param[in] stack stack to fetch data
 /param[in] output_data array of elements from Stack

 /return size of output_data
*/
size_t StackGetAll(Stack* stack, data_stack* output_data)
{
	return stack->size;
}
/**
 /brief Calculate resizing value of stack

 /param[in] stack stack to calculate size // default is 'u'
 /param[in] mode mode for calculating 'u' - resize up , and 'd' - resize down

 /return value to resize stack under zero on positive
*/
int StackCalcResize(Stack* stack, char mode = 'u') /// to-do assert and err mesaging
{
	if (mode == 'u') { // step up algorithm
		if (stack->capacity < 5) {
			return 5;
		}
		else if (stack->capacity > 4) {
			if (stack->capacity * 2 < STACK_MAX_CAPCITY) {
				return (stack->capacity << 1);
			}
			else {
				return STACK_MAX_CAPCITY;
			}
		}
	}
	else if(mode == 'd') { // step down algorithm
		if (stack->capacity < 5) {
			return stack->size;
		}
		else if (stack->capacity > 4) {
			if (stack->capacity / 2 > stack->size) {
				return (stack->capacity >> 1);
			}
			else {
				return stack->size + stack->size / 4;
			}
		}
	}
	else {
		return STACK_BAD_ARGS;
	}
}