#include <stdio.h>
#include "../../../stack_c/stack_c/Stack.h"

int main()
{
	printf("Hello World!\n");

	Stack *ex = nullptr;

	ex = StackCtorDin();
	StackPush(ex, 4235775);
	printf("%d", StackPop(ex));
	StackDtorDin(ex);

	printf("\n\n");

	system("pause");
}