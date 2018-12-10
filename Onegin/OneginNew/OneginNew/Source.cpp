#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#include "..\..\..\..\Libs\FileReaderLib\ReaderLib.h"

#define FILE_INPUT "../data/input1.txt"
#define FILE_FOR_OUTPUT "../data/output.txt"

int ReverseCompare(const void* a, const void* b);

int main()
{
    char * buf_for_input = nullptr;
    size_t file_size = ReadFromFile(FILE_INPUT, &buf_for_input);
    puts(buf_for_input);

    char ** strings = nullptr;
    size_t strings_amount = ParseStringToStrings(buf_for_input, &strings);

    free(buf_for_input);
    PrintStrings(strings, strings_amount);

    qsort(strings, strings_amount, sizeof(char*), ReverseCompare);
    PrintStrings(strings, strings_amount);
    if (!SaveStringsToFile(FILE_FOR_OUTPUT, strings, strings_amount)) {
        puts("can't save to file");
    }

    FreeStrings(strings, strings_amount);

    puts("\n enter to exit");
    getc(stdin);
    return 0;
}

int ReverseCompare(const void* a, const void* b)
{
    const char* arg1 = *(const char**)a;
    const char* arg2 = *(const char**)b;


    const char* arg1copy = *(const char**)a;
    const char* arg2copy = *(const char**)b;

    size_t len1 = strlen(arg1);
    size_t len2 = strlen(arg2);

    arg1copy += len1 - 1;
    arg2copy += len2 - 1;

    if (*arg1 == '\0') {
        if (*arg2 == '\0') {
            return 0;
        }
        else {
            return -1;
        }
    }
    if (*arg2 == '\0') {
        return 1;
    }

    while (arg1copy >= arg1 && arg2copy >= arg2) {
        if (*arg1copy == *arg2copy) {
            arg1copy--;
            arg2copy--;
            continue;
        }
        else if (!isalpha(*arg1copy)) {
            arg1copy--;
        }
        else if (!isalpha(*arg2copy)) {
            arg2copy--;
        }
        else if (*arg1copy > *arg2copy) {
            return 1;
        }
        else {
            return -1;
        }
    }


    return 0;
}