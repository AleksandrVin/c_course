#pragma once

#include <stdio.h>

#include "../../../stack_c/stack_c/Stack.h"
#include "../global_prop.h"
#include "defines.h"

#include <assert.h>

struct Process {
    size_t id;
    size_t position;
    bool running = false;
    char * buf_input = nullptr;
    size_t size_of_buf_input;
    Stack * stack;
    int * ram;
    size_t ram_ammount;
    int registers[REGISTERS_AMOUNT];
};

size_t RunProces(Process * process);

Process* CreateProcessDin(size_t id, const char * file);
size_t DestructProcess(Process * process);

FILE * OpenFile(const char * file_to_open, const char * mode);
size_t GetFileSize(FILE* file_to_seek);

int ReadNumber(char * data);
