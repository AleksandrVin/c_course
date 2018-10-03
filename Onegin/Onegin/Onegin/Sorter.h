#pragma once

#ifndef SORTER
#define SORTER

#include <iostream>

#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h> 

class Sorter
{
public:
	Sorter(const char* file_input);
	~Sorter();
	bool SaveSorted(const char* file_output);
	bool SaveMixed(const char* file_output);
private:
	size_t getFileSize(FILE *file_to_seek);
    int parseToSrings(const char *buff, size_t size_of_buff);
	char **strings; // array of pointers to strings 
	char **strings_sorted; // array of pinters to sorted stirng 
	FILE *file;
	char *char_buff; //buff to read form file
	int readFromFile(const char* file_input);
	int nStrings = 0;
	int countStrings(const char* buff, size_t size_of_buff);
	const char *stringCopy(char* str_to, const char* str_from, int begin_from , int lenght, int begin_to);
	int reverseCompare(const void* a, const void* b);
	void copy_strings_to_strings_sorted(int nStrings); // copy strings to strings_sorted 
	int cmp(const void*a, const void *b);
protected:
	bool File_readed = false;
	int printStrings(int strings_amount, char** strings);
	int findSizeOfString(const char* string);
};

#endif // !SORTER