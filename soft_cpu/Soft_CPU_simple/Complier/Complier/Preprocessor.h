#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "MacrosLib/macros.h"
#include "FileReaderLib/ReaderLib.h"

bool Preprocess(const char * file_input_name, const char * file_output_name);

size_t ClearStrings(char *** strings, size_t strings_amount);

size_t DellComments(char *** strings, size_t strings_amount);

size_t DellClearlines(char *** strings, size_t strings_amount);

bool SaveStringsToFileCustom(const char * file_name, char ** strings, size_t strings_amount);
