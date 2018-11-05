#include "Compiler.h"

Compiler * CompilerCtorDin()
{
    Compiler* progect = (Compiler*)calloc(1, sizeof(Compiler));
    assert(progect != nullptr);
    progect->CONF = 0x00; // defaut config 
    progect->buf_input = nullptr;
    progect->size_of_buf_input = 0;
    progect->strings = nullptr; // array of pointers to strings
    progect->string_amount = 0;
    return progect;
}

size_t CompilerDtorDin(Compiler * progect)
{
    //StringsMemClear(progect);
    free(progect);
    return 0;
}

size_t StringsMemClear(Compiler * progect)
{
    assert(progect != nullptr);
    assert(progect->strings != nullptr);
    size_t i = 0;
    for (i; i < progect->string_amount; i++) {
        if (progect->strings[i] != nullptr) {
            free(progect->strings[i]);
            progect->strings[i] = nullptr;
        }
    }
    free(progect->strings);
    progect->strings = nullptr;
    return i;
}

size_t CompilerPreprocessor(Compiler* progect, const char* file_to_read, const char * file_to_write)
{
    assert(progect != nullptr);

    PrepareStringsToSave(progect, file_to_read);

    FILE* FILE_output = OpenFile(progect, file_to_write, "w");
    if (FILE_output == nullptr) {
        StringsMemClear(progect);
        return 0;
    }

    size_t writed_to_file_strinngs = 0;
    for (size_t i = 0; i < progect->string_amount; i++) {
        if (progect->strings[i] != nullptr) {
            if (writed_to_file_strinngs > 0) {
                fprintf_s(FILE_output, "\n");
            }
            fprintf_s(FILE_output, "%s", progect->strings[i]);
            writed_to_file_strinngs++;
        }
    }

    fclose(FILE_output);
    StringsMemClear(progect);
    free(progect->buf_input);
    progect->buf_input = nullptr;
    return writed_to_file_strinngs;
}



size_t ClearStrings(Compiler * progect) /// make it ! // this function deletes coments and so on 
{
    assert(progect != nullptr);
    size_t free_lines = DellClearlines(progect);
    size_t comments = DellComments(progect);
    return free_lines + comments;
}

size_t DellComments(Compiler * progect)
{
    assert(progect != nullptr);
    assert(progect->strings != nullptr);
    size_t comment_lines = 0;
    char * comment_start = nullptr;
    for (size_t i = 0; i < progect->string_amount; i++)
    {
        if (progect->strings[i] == nullptr) {
            continue;
        }
        if ((comment_start = strchr(progect->strings[i], '#')))
        {
            char * string_buf = (char*)calloc(comment_start - progect->strings[i] + 1, sizeof(char));
            strncpy_s(string_buf, comment_start - progect->strings[i] + 1, progect->strings[i], comment_start - progect->strings[i]);
            free(progect->strings[i]);
            progect->strings[i] = string_buf;
            comment_lines++;
        }
    }
    return comment_lines;
}

size_t DellClearlines(Compiler * progect)
{
    assert(progect != nullptr);
    assert(progect->strings != nullptr);
    size_t clear_lines = 0;
    for (size_t i = 0; i < progect->string_amount; i++)
    {
        if (strlen(progect->strings[i]) == 0)
        {
            clear_lines++;
            assert(progect->strings[i] != nullptr);
            free(progect->strings[i]);
            progect->strings[i] = nullptr;
        }
    }
    return clear_lines;
}





size_t GetFileSize(FILE* file_to_seek)
{
    fseek(file_to_seek, 0, SEEK_END); // seek to end 
    size_t file_size = ftell(file_to_seek); // gets end position
    fseek(file_to_seek, 0, SEEK_SET); // seek to start
    return file_size;
}

int ParseToSrings(Compiler* progect)
{
    int string_counter = CountStrings(progect->buf_input, progect->size_of_buf_input);
    progect->strings = (char**)calloc(string_counter, sizeof(char*));
    progect->string_amount = 0;
    char * buf_copy = progect->buf_input;
    char * buf_end = buf_copy + progect->size_of_buf_input;
    char * last_string = buf_copy;
    for (buf_copy; buf_copy < buf_end; buf_copy++)
    {
        if (*buf_copy == '\n') {
            (progect->strings)[progect->string_amount] = (char*)calloc(buf_copy - last_string + 1, sizeof(char));
            size_t i = 0;
            for (last_string; last_string < buf_copy; last_string++) {
                progect->strings[progect->string_amount][i] = *last_string;
                i++;
            }
            progect->strings[progect->string_amount][i] = '\0';
            progect->string_amount++;
            last_string = buf_copy + 1;
        }
    }
    if (last_string != buf_copy + 1) {
        (progect->strings)[progect->string_amount] = (char*)calloc(buf_end - last_string + 1, sizeof(char));
        size_t i = 0;
        for (last_string; last_string < (buf_end); last_string++) {
            progect->strings[progect->string_amount][i] = *last_string;
            i++;
        }
        progect->strings[progect->string_amount][i] = '\0';
        progect->string_amount++;
    }
    return progect->string_amount;
}
int CountStrings(const char * buff, size_t size_of_buff)
{
    int string_counter = 0;
    for (size_t i = 0; i < size_of_buff; i++)
    {
        if (buff[i] == '\n') {
            string_counter++;
        }
    }
    if (buff[size_of_buff - 1] != '/n') {
        string_counter++;
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
        if (strings[i] != nullptr) {
            printf("{%s}\n", strings[i]);
        }
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


size_t PrepareStringsToSave(Compiler * progect, const char * file_to_read)
{

    FILE* file = OpenFile(progect, file_to_read, "r");
    if (file == nullptr) {
        return 0;
    }

    progect->size_of_buf_input = GetFileSize(file);
    progect->buf_input = (char*)calloc(progect->size_of_buf_input, sizeof(char));
    progect->size_of_buf_input = fread_s(progect->buf_input, progect->size_of_buf_input, sizeof(char), progect->size_of_buf_input, file);
    fclose(file);
    progect->string_amount = ParseToSrings(progect);

    size_t after_clearing = ClearStrings(progect);
    return after_clearing;
}