/**
 /file
 /brief realization of Stack

 /author Vinogradov Aleksandr
*/
#include "Stack.h"

Stack* StackCtorDin(size_t size_to_init) 
{
	Stack *stack = (Stack*)calloc(1, sizeof(Stack));
	StackCtor(stack, size_to_init);
	return stack;
}


int StackCtor(Stack* stack, size_t size_to_init) 
{
	stack->data = (data_stack*)calloc(size_to_init, sizeof(data_stack));
	stack->capacity = size_to_init;
	stack->size = size_to_init;
	stack->stack_state = STACK_GOOD;
	return size_to_init;
}


int StackDtor(Stack* stack) 
{
	size_t stack_size = stack->size;
	free(stack->data);
	stack->stack_state = STACK_NOT_EXIST;
	stack->data = nullptr;
	stack->capacity = STACK_NOT_EXIST;
	stack->size = STACK_NOT_EXIST;
	return stack_size;
}


int StackDtorDin(Stack* stack) 
{
	size_t size = StackDtor(stack);
	free(stack);
	return size;
}

int StackClean(Stack* stack)
{
	if (!StackOk(stack)) {
		return STACK_BROKEN;
	}
	size_t stack_size = stack->size;
	for (stack->size--; stack->size > 0; stack->size--)
	{
		stack->data[stack->size] = 0;
	}
	return stack_size;
}

int StackFree(Stack* stack)
{
	if (!StackOk(stack)) {
		return STACK_BROKEN;
	}
	size_t stack_size = stack->size;
	free(stack->data);
	stack->size = 0;
	stack->capacity = 0;
	stack->data = nullptr;
	stack->stack_state = STACK_NOT_EXIST;
	return stack_size;
}

int StackPush(Stack* stack, data_stack data) 
{
	if (!StackOk(stack)) {
		return STACK_BROKEN;
	}
	if (!(stack->size < stack->capacity)) {
		int status = StackRealloc(stack, 'u');
		if (!(status == STACK_GOOD)) {
			stack->stack_state = status;
			return status;
		}
	}
	stack->data[stack->size] = data;
	stack->size++;
	return STACK_GOOD;
}

int StackRealloc(Stack* stack, char mode)
{
	if (!StackOk(stack)) {
		return STACK_BROKEN;
	}
	int resize = StackCalcResize(stack, mode);
	if (stack->capacity != resize) {
		data_stack* new_ptr = (data_stack*)realloc(stack->data, resize * sizeof(data_stack));
		if (new_ptr) {
			stack->data = new_ptr;
			stack->capacity = resize;
			return STACK_GOOD;
		}
		////
		system(MEM_SHOP); ///ficha
		////
		return STACK_LACK_OF_MEMORY;
	}
	return STACK_GOOD;
}

int StackOk(Stack* stack) /// add hash sum and memcheck advanced features 
{
	if (stack->data == nullptr) {
		return STACK_NOT_EXIST;
	}
	if (stack->size > stack->capacity) {
		return STACK_BROKEN;
	}
	if (stack->size < 0 && stack->capacity < 0) {
		return STACK_NOT_EXIST;
	}
	return STACK_GOOD;
}

void StackDump(Stack* stack)
{
	if (StackOk(stack) != STACK_GOOD) {
		printf("\n\nStack [0x%p] (ERROR!)\n{\n\t", stack);
		printf("capacity = %d\n\t", stack->capacity);
		printf("size = %d\n\t", stack->size);
		printf("stack_state = %d\n\t", stack->stack_state);
		printf("data[%d] : [0x%p]\n\t{\n", stack->capacity, stack->data);
		for (size_t i = 0; i < stack->capacity; i++)
		{
			if (stack->size <= stack->capacity) {
				printf("\t\t*[%d] = %d\n", i, stack->data[i]);
			}
			else {
				printf("\t\t[%d] = %d\n", i, stack->data[i]);
			}
		}
		printf("\t}\n}\n");
	}
	else {
		printf("\n\nStack [0x%p] (GOOD) \n{\n\t", stack);
		printf("capacity = %d\n\t", stack->capacity);
		printf("size = %d\n\t", stack->size);
		printf("stack_state = %d\n\t", stack->stack_state);
		printf("data[%d] : [0x%p]\n\t{\n", stack->capacity, stack->data);
		for (size_t i = 0; i < stack->capacity; i++)
		{
			if (stack->size <= stack->capacity) {
				printf("\t\t*[%d] = %d\n", i, stack->data[i]);
			}
			else {
				printf("\t\t[%d] = %d\n", i, stack->data[i]);
			}
		}
		printf("\t}\n}\n");
	}
}

int StackResize(Stack* stack, int new_stack_capacity)
{
	if (!StackOk(stack)) {
		return STACK_BROKEN;
	}
	if (new_stack_capacity == 0) {
		StackFree(stack);
		return new_stack_capacity;
	}
	if (new_stack_capacity > 0) {
		data_stack* new_ptr = (data_stack*)realloc(stack->data, new_stack_capacity * sizeof(data_stack));
		if (new_ptr) {
			stack->data = new_ptr;
			stack->capacity = new_stack_capacity;
			if ((int)stack->size > new_stack_capacity) {
				stack->size = new_stack_capacity;
			}
			return new_stack_capacity;
		}
		else {
			////
			system(MEM_SHOP); ///ficha
			////
			return STACK_LACK_OF_MEMORY;
		}
	}
	return STACK_BAD_ARGS;
}


int StackSrink_to_fit(Stack* stack)
{
	if (StackOk(stack)) {
		return STACK_BROKEN;
	}
	data_stack* new_ptr = (data_stack*)realloc(stack->data, stack->size * sizeof(data_stack));
	if (new_ptr) {
		stack->data = new_ptr;
		stack->capacity = stack->size;
		return stack->size;
	}
	////
	system(MEM_SHOP); ///ficha
	////
	return STACK_LACK_OF_MEMORY;
}


/* unmaked
size_t StackMaxCapacity(Stack* stack)
{
	return 0;
}
*/


data_stack StackPop(Stack* stack)
{
	if (stack->size > 0) {
		data_stack data = stack->data[stack->size - 1];
		stack->size--;
		int status = StackRealloc(stack, 'd');
		stack->stack_state = status;
		return data;
	}
	else {
		return (data_stack)STACK_UNDERFLOW;
	}
	return (data_stack)STACK_UNNOWN_ERROR;
}

data_stack StackFront(Stack* stack)
{
	if (stack->size > 0) {
		return stack->data[stack->size - 1];
	}
	return 0;
}

size_t StackGetAll(Stack* stack, data_stack* output_data) /// make it 
{
	return STACK_UNNOWN_ERROR;
}

int StackCalcResize(Stack* stack, char mode) /// to-do assert and err mesaging
{
	if (mode == 'u') {  // step up algorithm
		if (stack->capacity < 5) {
			return 5;
		}
		else if (stack->capacity > 4) {
			//if (stack->capacity * 2 < STACK_MAX_CAPCITY) {
			return (stack->capacity * 2);
			//}
				/*
			else {
				return STACK_MAX_CAPCITY;
			}
			*/
		}
	}
	else if (mode == 'd') { // step down algorithm
		if (stack->capacity < 5) {
			return 5;
		}
		else if (stack->capacity > 2) {
			if (stack->capacity / 2 > stack->size) {
				return (stack->capacity / 2);
			}
			else {
				return stack->capacity;
			}
		}
	}
	else {
		return STACK_BAD_ARGS;
	}
	return STACK_UNNOWN_ERROR;
}