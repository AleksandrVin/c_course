#include "pch.h"

size_t ReadFromFile(const char * file_input, char ** string_for_result)
{
    ///opening file
    FILE* FILE_input;
    errno_t file_state = fopen_s(&FILE_input, file_input, "r");
    if (file_state) {
        LOG_ERR("can't open file read in preprocessor", file_input);
        return 0;
    }

    ///preparing space for string
    size_t size_of_string_for_result = GetFileSize(FILE_input) + 1; // becouse we need space for '\0'
    *string_for_result = (char*)calloc(size_of_string_for_result, sizeof(char));

    ///reading from file with low lever function
    size_of_string_for_result = fread_s(*string_for_result, size_of_string_for_result, sizeof(char), size_of_string_for_result, FILE_input);

    ///closing file
    fclose(FILE_input);

    ///add '\0' to string
    *(string_for_result + size_of_string_for_result - 1) = '\0'; // -1 becouse we need to step 1 step left in string

    return size_of_string_for_result;
}

void PrintString(const char * string, FILE * FILE_output)
{
    assert(string != nullptr);
    fputs(string, FILE_output);
}


size_t GetFileSize(FILE* file_to_seek)
{
    fseek(file_to_seek, 0, SEEK_END); // seek to end 
    size_t file_size = ftell(file_to_seek); // gets end position
    fseek(file_to_seek, 0, SEEK_SET); // seek to start
    return file_size;
}