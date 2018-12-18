#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "MacrosLib/macros.h"
#include "FileReaderLib/ReaderLib.h"
#include "ListLib/listChar.h"

#include "settings.h"

//update when change registers
#define REGISTERS_AMOUNT 4

struct Command {
    char command_raw[MAX_LENGTH_OF_COMMAND];
    char number_raw[MAX_LENGTH_OF_COMMAND];
    _cmd command = 0;
    unsigned char mode = 0; // mode of commannd 
    _data number = 0; 
    _index index = 0; // or number of register 
};

struct Label {
    char label[MAX_LENGTH_OF_COMMAND];
    _index row = 0;
};

// return 0 if error
bool Compiler(const char * file_input_name, const char * file_output_name, Label * labels, bool label_set, size_t * labels_amount);

size_t ParseString(const char * string_to_parse, Command * line_parsed);

size_t SaveNumber(FILE * file, _index number);

size_t SaveData(FILE * file, _data number);

_index CompareRegister(const char * register_raw);

_index SearchLabel(const char * string_to_search, Label * labels, size_t labels_amount);
