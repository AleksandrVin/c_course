#include "tests.h"

bool Test43_42(Stack* stack)
{
	total_passed = 10 - 1;
	for (passed; passed < 10; passed++, total_passed--)
	{
		StackPush(stack, 50);
		UNITTEST(StackPop(stack), 50);
	}
	return true;
}

bool TestPushPop10(Stack* stack, int elem_to_push)
{
	total_passed = 10 - 1;
	for (passed = 0; passed < 10; passed++, total_passed--)
	{
		StackPush(stack, elem_to_push);
		UNITTEST(StackPop(stack), elem_to_push);
	}
	return true;
}

bool TestTestDump(Stack* stack)
{
	total_passed = 10 - 1;
	for (passed = 0; passed < 10; passed++, total_passed--)
	{
		StackPush(stack, 11111);
	}
	StackDump(stack);
	return true;
}

bool TestTryPopEmpty(Stack* stack)
{
	total_passed = 10 - 1;
	for (passed = 0; passed < 10; passed++, total_passed--)
	{
		UNITTEST(StackPop(stack), STACK_UNDERFLOW);
	}
	StackDump(stack);
	return true;
}

bool TestTryGetLast(Stack* stack)
{
	total_passed = 10 - 1;
	for (size_t i = 0; i < 5; i++)
	{
		StackPush(stack, 1111);
	}
	for (passed = 0; passed < 10; passed++, total_passed--)
	{
		UNITTEST(StackPop(stack), 1111);
	}
	StackDump(stack);
	return true;
}

bool TestPushAndPopLarge(Stack* stack)
{
	total_passed = 10 - 1;
	size_t tests = 500000000000;
	for (passed = 0; passed < 10; passed++, total_passed--)
	{
		for (int i = 0; i <= tests; i++)
		{
			StackPush(stack, i);
		}
		for (int i = tests; i >= 0; i--)
		{
			UNITTEST_FAST(StackPop(stack), i);
		}
		printf("\n passed \n");
	}
	return true;
}