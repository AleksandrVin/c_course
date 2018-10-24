/**
 /file
 /brief realization of Stack

 /author Vinogradov Aleksandr
*/

#include "Stack.h"

Stack* StackCtorDin(size_t size_to_init)
{
	Stack *stack = (Stack*)calloc(1, sizeof(Stack));
	if (stack == nullptr) {
		ERROR_LOG(STACK_LACK_OF_MEMORY, M_STACK_LACK_OF_MEMORY, STACK_NOT_EXIST, M_STACK_NOT_EXIST, stack);
		return nullptr;
	}
	int status = StackCtor(stack, size_to_init);
	if (status != STACK_GOOD) {
		ERROR_LOG(status, "ERROR_IN_Ctor", stack->stack_state, "Stack was initialized broken", stack);
	}
	return stack;
}


int StackCtor(Stack* stack, size_t size_to_init)
{
	if (stack == nullptr) {
		ERROR_LOG(STACK_BAD_ARGS, M_STACK_BAD_ARGS, STACK_NOT_EXIST, M_STACK_NOT_EXIST, stack);
		return STACK_BAD_ARGS;
	}
	stack->data = (data_stack*)calloc(size_to_init, sizeof(data_stack));
	if (stack->data == nullptr) {

		ERROR_LOG(STACK_LACK_OF_MEMORY, M_STACK_LACK_OF_MEMORY, STACK_NOT_EXIST, M_STACK_NOT_EXIST, stack);
		return STACK_LACK_OF_MEMORY;
	}
	stack->capacity = size_to_init;
	stack->size = 0;
	stack->mem_protect_begin = STACK_MEM_PROTECT;
	stack->mem_protect_end = STACK_MEM_PROTECT;
	stack->stack_state = STACK_GOOD;
	return STACK_GOOD;
}


int StackDtor(Stack* stack)
{
	if (stack == nullptr) {
		ERROR_LOG(STACK_BAD_ARGS, M_STACK_BAD_ARGS, STACK_NOT_EXIST, M_STACK_NOT_EXIST, stack);
		return STACK_BAD_ARGS;
	}
	size_t stack_size = stack->size;
	free(stack->data);
	stack->stack_state = STACK_NOT_EXIST;
	stack->data = nullptr;
	stack->capacity = NULL;
	stack->size = NULL;
	return stack_size;
}


int StackDtorDin(Stack* stack)
{
	if (stack == nullptr) {
		ERROR_LOG(STACK_BAD_ARGS, M_STACK_BAD_ARGS, STACK_NOT_EXIST, M_STACK_NOT_EXIST, stack);
		return STACK_BAD_ARGS;
	}
	size_t size = StackDtor(stack);
	free(stack);
	return size;
}

int StackClean(Stack* stack)
{
	if (!StackOk(stack)) {
		ERROR_LOG(STACK_BROKEN, M_STACK_BROKEN, StackOk(stack), "stack not good", stack);
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
		ERROR_LOG(STACK_BROKEN, M_STACK_BROKEN, StackOk(stack), "stack not good", stack);
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
		ERROR_LOG(STACK_BROKEN, M_STACK_BROKEN, StackOk(stack), "stack not good", stack);
		return STACK_BROKEN;
	}
	if (!(stack->size < stack->capacity)) {
		int status = StackRealloc(stack, 'u');
		if (!(status == STACK_GOOD)) {
			ERROR_LOG(status, "error in push", stack->stack_state, "stack not good", stack);
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
		ERROR_LOG(STACK_BROKEN, M_STACK_BROKEN, StackOk(stack), "stack not good", stack);
		return STACK_BROKEN;
	}
	int resize = StackCalcResize(stack, mode);
	if (stack->capacity != resize) {
		data_stack* new_ptr = (data_stack*)_recalloc(stack->data, resize, sizeof(data_stack));
		if (new_ptr) {
			stack->data = new_ptr;
			stack->capacity = resize;
			return STACK_GOOD;
		}
		////
		system(MEM_SHOP); ///ficha
		////
		ERROR_LOG(STACK_LACK_OF_MEMORY, M_STACK_LACK_OF_MEMORY, stack->stack_state, "stack not good", stack);
		return STACK_LACK_OF_MEMORY;
	}
	return STACK_GOOD;
}

bool StackOk(Stack* stack) /// add hash sum and memcheck advanced features 
{
	if (stack == nullptr) {
		return STACK_BROKEN;
	}
	if (stack->stack_state != STACK_GOOD) {
		return STACK_BROKEN;
	}
	if (stack->data == nullptr) {
		return STACK_BROKEN;
	}
	if (stack->size > stack->capacity) {
		return STACK_BROKEN;
	}
	if (stack->size < 0 && stack->capacity < 0) {
		return STACK_BROKEN;
	}
	if (stack->mem_protect_begin != STACK_MEM_PROTECT)
	{
		return STACK_BROKEN;
	}
	if (stack->mem_protect_end != STACK_MEM_PROTECT)
	{
		return STACK_BROKEN;
	}
	return STACK_GOOD;
}

void StackDump(Stack* stack, FILE* stream)
{
	if (stack == nullptr) {
		fprintf(stream, "\n\nStack [0x%p] (ERROR!)\n{\n", stack);
		fprintf(stream, "\tStack == nullptr\n}\n");
	}
	else if (StackOk(stack) != STACK_GOOD) {
		fprintf(stream, "\n\nStack [0x%p] (ERROR!)\n{\n\t", stack);
		fprintf(stream, "capacity = %d\n\t", stack->capacity);
		fprintf(stream, "size = %d\n\t", stack->size);
		fprintf(stream, "stack_state = %d\n\t", stack->stack_state);
		fprintf(stream, "data[%d] : [0x%p]\n\t{\n", stack->capacity, stack->data);
		for (size_t i = 0; i < stack->capacity; i++)
		{
			if (stack->size <= stack->capacity) {
				fprintf(stream, "\t\t*[%d] = %d\n", i, stack->data[i]);
			}
			else {
				fprintf(stream, "\t\t[%d] = %d\n", i, stack->data[i]);
			}
		}
		fprintf(stream, "\t}\n}\n");
	}
	else {
		fprintf(stream, "\n\nStack [0x%p] (GOOD) \n{\n\t", stack);
		fprintf(stream, "capacity = %d\n\t", stack->capacity);
		fprintf(stream, "size = %d\n\t", stack->size);
		fprintf(stream, "stack_state = %d\n\t", stack->stack_state);
		fprintf(stream, "data[%d] : [0x%p]\n\t{\n", stack->capacity, stack->data);
		for (size_t i = 0; i < stack->capacity; i++)
		{
			if (stack->size <= stack->capacity) {
				fprintf(stream, "\t\t*[%d] = %d\n", i, stack->data[i]);
			}
			else {
				fprintf(stream, "\t\t[%d] = %d\n", i, stack->data[i]);
			}
		}
		fprintf(stream, "\t}\n}\n");
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


data_stack StackPop(Stack* stack)
{
	if (!StackOk(stack)) {
		return STACK_BROKEN;
	}
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
	return (data_stack)STACK_UNKNOWN_ERROR;
}

data_stack StackFront(Stack* stack)
{
	if (!StackOk(stack)) {
		return STACK_BROKEN;
	}
	if (stack->size > 0) {
		return stack->data[stack->size - 1];
	}
	return 0;
}

//size_t StackGetAll(Stack* stack, data_stack* output_data) /// make it 
//{
//	return STACK_UNKNOWN_ERROR;
//}

int StackCalcResize(Stack* stack, char mode) /// to-do assert and err mesaging
{
	if (!StackOk(stack)) {
		return STACK_BROKEN;
	}
	if (mode == 'u') {  // step up algorithm
		if (stack->capacity < STACK_PERMANENT_CAPACITY) {
			return STACK_PERMANENT_CAPACITY;
		}
		else {
			return (stack->capacity * STACK_RESIZE_UP_COEFICIENT);
		}
	}
	else if (mode == 'd') { // step down algorithm
		if (stack->capacity < STACK_PERMANENT_CAPACITY) {
			return STACK_PERMANENT_CAPACITY;
		}
		else if (stack->capacity > STACK_RESIZE_DOWN_COEFICIENT) {
			if (stack->capacity / STACK_RESIZE_DOWN_COEFICIENT > stack->size) {
				return (stack->capacity / STACK_RESIZE_DOWN_COEFICIENT);
			}
			else {
				return stack->capacity;
			}
		}
	}
	else {
		return STACK_BAD_ARGS;
	}
	return STACK_UNKNOWN_ERROR;
}