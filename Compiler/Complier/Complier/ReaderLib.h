
/**
 \brief lib for reading file

 @note use it careful becouse this lib is powerfull but may be not so protected
*/

#pragma once

/**
 /brief Read text file to char buff and calloc memory for them

 /param[in]  file_input name of file on disk to read
 /param[in]  string_for_result poiter for string for output result
 /return size_t count of readed simbols
*/
size_t ReadFromFile(const char * file_input, char ** string_for_result);




/**
 /brief just print string

 @note you can specify output stream

 /param[in] string pointer for first string char

 /param[in] FILE_output output stream , default is stdout
*/
void PrintString(const char * string, FILE * FILE_output = stdout);

/**
 /brief measure size of file on disk

 @note provide opened FILE
 @note measure using file seek

 /param[in]  file_to_seek pointer to FILE structure
 /return size_t size of file
*/
size_t GetFileSize(FILE* file_to_seek);