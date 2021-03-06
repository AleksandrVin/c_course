#include "config.h"

#include <stdio.h>
#include <stdlib.h>



#include "Stack.h" /// sourse file of Stack



//#include "unittest.h" /// use unittest #defines for debuging Stack
#include "tests.h"

int main()
{
	Stack *ex = nullptr;

	ex = StackCtorDin();
	Test43_42(ex);
	StackDtorDin(ex);

	printf("\n\n");

	ex = StackCtorDin();
	TestTestDump(ex);
	StackDtorDin(ex);

	printf("\n\n");

	ex = StackCtorDin();
	//ex->stack_state = STACK_NOT_EXIST;
	//ex->size = ex->capacity + 1;
	TestTestDump(ex);
	StackDtorDin(ex);

	printf("\n\n");

	ex = StackCtorDin();
	TestTryPopEmpty(ex);
	StackDtorDin(ex);

	printf("\n\n");

	ex = StackCtorDin();
	TestTryGetLast(ex);
	StackDtorDin(ex);

	printf("\n\n");

	ex = StackCtorDin();
	//TestPushAndPopLarge(ex);
	StackDtorDin(ex);
	ex = (Stack*)nullptr;
	StackDtorDin(ex);
	printf("\n\n");

	printf("\n");
	system("pause");
	return 0;
}