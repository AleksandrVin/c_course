#include <stdio.h>
#include <stdlib.h>

#include "Stack.h" /// sourse file of Stack

#define DEBUGING

//#include "unittest.h" /// use unittest #defines for debuging Stack
#include "tests.h"

int main()
{

	Stack *ex = StackCtorDin();
	Test43_42(ex);
	StackPush(ex, 55);
	StackPush(ex, 55);
	StackPush(ex, 55);
	StackPush(ex, 55); 
	StackPush(ex, 55);
	StackPush(ex, 55);
	ex->stack_state = STACK_NOT_EXIST;
	StackDump(ex);
	StackDtorDin(ex);
	//StackPush(ex, 42);
	//StackPush(ex, 43);
	//printf("%d\n", StackPop(ex));
	//printf("%d\n", StackPop(ex));
	printf("\n");
	system("pause");
	return 0;
}