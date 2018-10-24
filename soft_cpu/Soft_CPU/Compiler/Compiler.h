/**
 /file
 /brief header for Compiler 

 /author Vinogradov Aleksandr
*/
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
//bite opt
const size_t COMAND_SIZE = 1 ;
const size_t DATA_SIZE = sizeof(int);

const char START_CODE = 0xFF;
const char END_CODE = 0xAA;

//works only with char*
#define LOG_ERR( message , data ) \
    fprintf(stderr, "\n\tERROR:  %s : %s" , message , data)

struct Compiler {
	char CONF = 0x00; // defaut config 
	char* buf_input = nullptr;
	size_t size_of_buf_input = 0;
	char **strings; // array of pointers to strings 
};

Compiler* CompilerCtorDin();
/**
 /brief delete all coments free lines and check for bag code
 
 /param progect config struct 
 /param file_to_preproc file to save work

 /return size of generated file
*/
size_t CompilerPreprocessor(Compiler* progect,const char*  file_to_read, const char* file_to_preproc);

/**
 /brief delete all coments free lines and check for bag code

 /param progect config struct
 /param file_to_preproc file to save work

 /return size of generated file
*/
size_t CompilerCompile(Compiler* progect,const char* file_to_preproc,const char* file_to_read);
size_t GetFileSize(FILE * file_to_seek);

size_t CheckString(Compiler* progect, char* string);

int CountStrings(const char* buff, size_t size_of_buff);
int ParseToSrings(Compiler* progect,const char* buff, size_t size_of_buff);
const char* StringCopy(char* str_to, const char* str_from, int begin_from, int lenght, int begin_to);
int PrintStrings(int strings_amount, char** strings);

