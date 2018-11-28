#pragma once

#include "pch.h"

size_t LoadStrings(const char * file_name, char *** strings);

Node * LoadTreeFromFile(const char * file_name, size_t string_amount);

int ParseToSrings(char * buf_input, size_t size_of_buf_input, char *** strings);

int CountStrings(const char * buff, size_t size_of_buff);

size_t GetFileSize(FILE* file_to_seek);

int PrintStrings(int strings_amount, char** strings);]

Node * ResolveNode(const char * buff);





