#include "Compiler.h"

Compiler * CompilerCtorDin()
{
    Compiler* progect = (Compiler*)calloc(1, sizeof(Compiler));
    assert(progect != nullptr);
    return progect;
}

size_t CompilerPreprocessor(Compiler* progect, const char* file_to_read, const char* file_output)
{
    if (progect == nullptr) {
        return 0;
    }
    FILE* FILE_input;
    errno_t file_state = fopen_s(&FILE_input, file_to_read, "r");
    if (file_state) {
        LOG_ERR("can't open file read in preprocessor", file_to_read);
        return 0;
    }
    size_t size_of_file = GetFileSize(FILE_input);
    char* text_buff = (char*)calloc(size_of_file, sizeof(char));
    size_t file_readed_size = fread_s(text_buff, size_of_file, sizeof(char), size_of_file, FILE_input);
    fclose(FILE_input);
    size_t strings_parsed = ParseToSrings(progect, text_buff, file_readed_size);
    size_t after_clearing = ClearStrings(progect);
    PrintStrings(strings_parsed, progect->strings);
    return file_readed_size; // remove it 
}

size_t CompilerCompile(Compiler * progect, const char * file_to_preproc, const char * file_to_read)
{
    return size_t();
}

size_t ParseString(Compiler * progect, const char * string_to_parse, Command * line_parsed)
{
    assert(progect != nullptr);
    assert(string_to_parse != nullptr);

    if (sscanf_s(string_to_parse, "%s %d", &(line_parsed->command), &(line_parsed->number)) == 2) { // format like {push 10}
        line_parsed->mode = MODE_NUMBER;
        return 2;
    }
    if (sscanf_s(string_to_parse, "%s [%d]", &(line_parsed->command), &(line_parsed->number)) == 2) { // format like {push [10]}
        line_parsed->mode = MODE_RAM;
        return 2;
    }
    if (sscanf_s(string_to_parse, "%s %s", &(line_parsed->command_raw), &(line_parsed->number_raw)) == 2) { // format like {push ax}
        line_parsed->mode = MODE_REGISTER;
        return 2;
    }
    if (sscanf_s(string_to_parse, "%s", &(line_parsed->command)) == 1) { // format like {add}
        line_parsed->mode = MODE_ACTION;
        return 1;
    }

    line_parsed->mode = MODE_ERR;
    return 0;
}

size_t ClearString(Compiler * progect) /// make it ! // this function deletes coments and so on 
{
    return 0;
}

size_t GetFileSize(FILE* file_to_seek)
{
    fseek(file_to_seek, 0, SEEK_END); // seek to end 
    size_t file_size = ftell(file_to_seek); // gets end position
    fseek(file_to_seek, 0, SEEK_SET); // seek to start
    return file_size;
}

int ParseToSrings(Compiler* progect, const char* buff, size_t size_of_buff)
{
    int string_counter = CountStrings(buff, size_of_buff);
    progect->strings = (char**)calloc(string_counter, sizeof(char*));
    int current_string_starts = 0;
    int current_string_lenght = 0;
    int current_string = 0;
    for (size_t i = 0; i < size_of_buff; i++)
    {
        if (buff[i] == '\n' && current_string_lenght) {
            progect->strings[current_string] = (char*)calloc(current_string_lenght, sizeof(char));
            StringCopy(progect->strings[current_string], buff, current_string_starts, current_string_lenght, 0);
            current_string++;
            ++current_string_starts += current_string_lenght;
            current_string_lenght = 0;
        }
        else if (buff[i] != '\n') {
            current_string_lenght++;
        }
    }
    return current_string;
}
int CountStrings(const char * buff, size_t size_of_buff)
{
    int string_counter = 0;
    bool last_was_free = true;
    for (size_t i = 0; i < size_of_buff; i++)
    {
        if (buff[i] == '\n' && !last_was_free) {
            last_was_free = true;
            string_counter++;
        }
        else if (buff[i] != '\n') {
            last_was_free = false;
        }
    }
    return string_counter;
}

const char* StringCopy(char* str_to, const char* str_from, int begin_from, int lenght, int begin_to)
{
    lenght += begin_from;
    for (begin_from; begin_from < lenght; begin_from++)
    {
        str_to[begin_to++] = str_from[begin_from];
    }
    str_to[begin_to] = '\0';
    return str_from;
}

int PrintStrings(int strings_amount, char** strings)
{
    for (int i = 0; i < strings_amount; i++)
    {
        printf("{%s}\n", strings[i]);
    }
    return strings_amount;
}

size_t CheckString(Compiler* progect, char* string, size_t size)
{
    assert(string != nullptr);
    size_t elems = 0;
    char* end_of_string = string + size;
    while (string++ < end_of_string) {
        if (*string != ' ') {
            elems++;
            while (isalpha(*string) || isdigit(*string)) {
                string++;
            }
        }
    }
    return elems;
}