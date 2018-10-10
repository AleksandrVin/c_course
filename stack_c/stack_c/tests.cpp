#include "tests.h"

bool Test43_42(Stack* stack)
{
	bool state = 1;
	for (passed; passed < 10; passed++, total_passed--)
	{
		StackPush(stack, 50);
		UNITTEST(StackPop(stack), 50);
	}
	return true;
}

bool TestPushPop10(Stack* stack, int elem_to_push)
{
	for (passed = 0; passed < 10; passed++, total_passed--)
	{
		StackPush(stack, elem_to_push);
		UNITTEST(StackPop(stack), elem_to_push);
	}
	return true;
}
