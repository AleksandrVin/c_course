#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#include "MacrosLib/macros.h"
#include "FileReaderLib/ReaderLib.h"
#include "StackLib/StackDouble.h"

#include "settings.h"

struct Process {
    size_t id;
    size_t position;
    bool running = false;
    char * buf_input = nullptr;
    size_t size_of_buf_input;
    Stack * stack = nullptr;
    _data ram[RAM_AMOUNT];
    size_t ram_ammount;
    _data registers[REGISTERS_AMOUNT];
    Stack * calls = nullptr;
};

Process * CreateProcessDin(size_t id, const char * file);

size_t DestructProcess(Process * process);

size_t RunProces(Process * process);

size_t ReadNumber(char * data);

_data ReadData(char * data);

size_t ReadFromFileBin(const char * file_input, char ** string_for_result);
