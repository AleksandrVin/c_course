/**
 /file
 /brief declaration of Stack

 /author Vinogradov Aleksandr
*/
#pragma once

#include <stdio.h>
#include <stdlib.h>

/**
 /note int , double , float , char types - ok
*/
typedef int data_stack; /// defined as double but you can override it 

enum STACK_STATES {
 STACK_UNDERFLOW  = -1,  /// enum make it 
 STACK_OVERFLOW  = -2,
 STACK_NOT_EXIST  = -3,
 STACK_TYPE_ERR  = -4,
 STACK_LACK_OF_MEMORY = -5,
 STACK_BAD_ARGS = -6,
 STACK_UNNOWN_ERROR = -10
};
//#define STACK_UNDERFLOW -1  /// enum make it 
//#define STACK_OVERFLOW -2
//#define STACK_NOT_EXIST -3
//#define STACK_TYPE_ERR -4
//#define STACK_LACK_OF_MEMORY -5
//#define STACK_BAD_ARGS -6
//#define STACK_UNNOWN_ERROR -10

#define MEM_SHOP "start http://newegg.com"

enum STACK_BOOL_STATES
{
	STACK_GOOD = 1,
	STACK_BROKEN = 0
};
//#define STACK_GOOD 1
//#define STACK_BROKEN 0

//#define MAX_BUFF 10000000
//#define STACK_MAX_CAPCITY ( MAX_BUFF / sizeof(data_stack) )

struct Stack
{
	data_stack *data = nullptr;
	size_t size = 0;
	size_t capacity = 0;
	int stack_state = STACK_NOT_EXIST;
};

/**
 /brief construct a Stack

 /param[in] stack stack to construct
 /param[in] size_of_init size of stack initializing // default is 0

 /return size of output_data or error messege
*/
int StackCtor(Stack* stack, size_t size_to_init = 0);
/**
 /brief construct a Stack using dimamic memory

 /param[in] size_of_init size of stack initializing // default is 0

 /return pointer to created Stack
*/
Stack* StackCtorDin(size_t size_to_init = 0);

/**
 /brief destruct a Stack

 /param[in] stack stack to destruct

 /return size of destructed or error messege
*/
int StackDtor(Stack* stack);
/**
 /brief destruct a Stack dinamic

 /param[in] stack stack to destruct dinamic

 /return size of destructed or error messege
*/
int StackDtorDin(Stack* stack);

/**
 /brief push one element to the end of the stack

 /param[in] stack stack to push
 /param[in] data element to push

 /return status stack or error messege
*/
int StackPush(Stack* stack, data_stack data);
/**
 /brief return and delete the last element of stak

 /param[in] stack stack to get elem

 /return last elem or 0 if now elements in stack or error
*/
data_stack StackPop(Stack* stack);
/**
 /brief get all data from Stack

 /param[in] stack stack to fetch data
 /param[in] output_data array of elements from Stack

 /return size of output_data
*/
size_t StackGetAll(Stack* stack, data_stack* output_data);
/**
 /brief give thirst elem of stack

 /param[in] stack stack to get elem

 /return last elem or 0 if now elements in stack or error
*/
data_stack StackFront(Stack* stack);
/**
 /brief free stack with deleting all data and allocated memory

 /param[in] stack stack to free

 /return size of deleted stack or error messege
*/
int StackFree(Stack* stack);
/**
 /brief cleen stack without resizing allocated memory for data

 /param[in] stack stack to cleen

 /return size of clened stack or error messege
*/
int StackClean(Stack* stack);
/**
 /brief check staus of stack

 /param[in] stack stack to check

 /return status of stack

 need to check state of stack based on internal structure
*/
int StackOk(Stack* stack);
/**
 /brief resize capasity to size of stack

 /param[in] stack stack to Srink

 /return new size or error
*/
int StackSrink_to_fit(Stack* stack);
/**
 /brief print stack status

 /param[in] stack stack to dump

 /return none

 beautifull debaging for stack
*/
void StackDump(Stack* stack);
/**
 /brief immediately realloc stack

 /param[in] stack stack to realloc

 /return new stack size or error message

 /note you can easy lost data from stack
*/
int StackResize(Stack* stack, int new_stack_capacity);
/**
 /brief Calculate resizing value of stack

 /param[in] stack stack to calculate size // default is 'u'
 /param[in] mode mode for calculating 'u' - resize up , and 'd' - resize down

 /return value to resize stack under zero on positive
*/
int StackCalcResize(Stack* stack, char mode = 'u');
/**
 /brief realloc allocated memory for stack based on StackReallocCalc

 /param[in] stack stack to free
 /param[in] mode 'u' to realloc up or 'd' to realloc down

 /return status of stack or error messege
*/
int StackRealloc(Stack* stack, char mode = 'u');