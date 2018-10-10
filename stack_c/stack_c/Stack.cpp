/**
 /file
 /brief realization of Stack

 /author Vinogradov Aleksandr
*/
#include "Stack.h"

/// make it using Stackstor 
Stack* StackCtorDin(size_t size_to_init) /// to-do assert and err mesaging
{
	Stack *stack = (Stack*)calloc(1, sizeof(Stack));
	stack->data = (data_stack*)calloc(size_to_init, sizeof(data_stack));
	stack->capacity = size_to_init;
	stack->size = size_to_init;
	stack->stack_state = STACK_GOOD;
	return stack;
}


int StackCtor(Stack* stack, size_t size_to_init) /// to-do assert and err mesaging
{
	stack->data = (data_stack*)calloc(size_to_init, sizeof(data_stack));
	stack->capacity = size_to_init;
	stack->size = size_to_init;
	stack->stack_state = STACK_GOOD;
	return size_to_init;
}


int StackDtor(Stack* stack) /// to-do assert and err mesaging
{
	if (StackOk(stack)) {
		size_t stack_size = stack->size;
		free(stack->data);
		stack->stack_state = STACK_NOT_EXIST;
		stack->data = nullptr;
		stack->capacity = STACK_NOT_EXIST;
		stack->size = STACK_NOT_EXIST;
		return stack_size;
	}
	return STACK_BROKEN;
}


int StackDtorDin(Stack* stack) /// to-do assert and err mesaging /// call it delete and make it from StackDtor
{
	if (StackOk(stack)) {
		size_t stack_size = stack->size;
		free(stack->data);
		free(stack);
		stack->stack_state = STACK_NOT_EXIST;
		stack->data = nullptr;
		stack->capacity = STACK_NOT_EXIST;
		stack->size = STACK_NOT_EXIST;
		return stack_size;
	}
	return STACK_BROKEN;
}

int StackClean(Stack* stack)
{
	if (StackOk(stack)) {
		size_t stack_size = stack->size;
		for (stack->size--; stack->size > 0; stack->size--)
		{
			stack->data[stack->size] = 0;
		}
		return stack_size;
	}
	return STACK_BROKEN;
}

int StackFree(Stack* stack)
{
	if (StackOk(stack)) {
		size_t stack_size = stack->size;
		free(stack->data);
		stack->size = 0;
		stack->capacity = 0;
		stack->data = nullptr;
		stack->stack_state = STACK_NOT_EXIST;
		return stack_size;
	}
	return STACK_BROKEN;
}

int StackPush(Stack* stack, data_stack data) /// make it 3 bloaks
{
	if (StackOk(stack)) {
		if (stack->size < stack->capacity) {
			stack->data[stack->size] = data;
			stack->size++;
			return STACK_GOOD;
		}
		else {
			int status = StackRealloc(stack, 'u');
			if (status == STACK_GOOD) {
				stack->data[stack->size] = data;
				stack->size++;
				return STACK_GOOD;
			}
			else {
				stack->stack_state = status;
				return status;
			}
		}
		return STACK_UNNOWN_ERROR;
	}
	return STACK_BROKEN;
}

int StackRealloc(Stack* stack, char mode)
{
	if (StackOk(stack)) {
		int resize = StackCalcResize(stack, mode);
		if (stack->capacity != resize) {
			data_stack* new_ptr = (data_stack*)realloc(stack->data, resize * sizeof(data_stack));
			if (new_ptr) {
				stack->data = new_ptr;
				stack->capacity = resize;
				return STACK_GOOD;
			}
			else {
				////
				system(MEM_SHOP); ///ficha
				////
				return STACK_LACK_OF_MEMORY;
			}
		}
		else
		{
			return STACK_GOOD;
		}
		return STACK_UNNOWN_ERROR;
	}
	return STACK_BROKEN;
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

void StackDump(Stack* stack) /// make it guy ! 
{
	if (StackOk(stack) != STACK_GOOD) {
		printf("\n\n Stack [0x%p] (ERROR!)\n{\n\t", stack);
		printf("capacity = %d\n\t", stack->capacity);
		printf("size = %d\n\t", stack->size);
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
		printf("\t}\n}");
	}
	else {
		printf("\n\n Stack [0x%p] (GOOD) \n{\n\t", stack);
		printf("capacity = %d\n\t", stack->capacity);
		printf("size = %d\n\t", stack->size);
		printf("data[%d] : [0x%p]\n\t{\n", stack->capacity, stack->data);
		for (size_t i = 0; i < stack->capacity; i++)
		{
			printf("\t\t*[%d] = %d\n", i, stack->data[i]);
		}
		printf("\t}\n}");
	}
}

int StackResize(Stack* stack, int new_stack_capacity)
{
	if (StackOk(stack)) {
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
		else if (new_stack_capacity == 0) {
			StackFree(stack);
			return new_stack_capacity;
		}
		return STACK_BAD_ARGS;
	}
	return STACK_BROKEN;
}

int StackSrink_to_fit(Stack* stack)
{
	if (StackOk(stack)) {
		data_stack* new_ptr = (data_stack*)realloc(stack->data, stack->size * sizeof(data_stack));
		if (new_ptr) {
			stack->data = new_ptr;
			stack->capacity = stack->size;
			return stack->size;
		}
		else {
			////
			system(MEM_SHOP); ///ficha
			////
			return STACK_LACK_OF_MEMORY;
		}
		return STACK_UNNOWN_ERROR;
	}
	return STACK_BROKEN;
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
	if (mode == 'u') { // step up algorithm
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
			return stack->capacity;
		}
		else if (stack->capacity > 4) {
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