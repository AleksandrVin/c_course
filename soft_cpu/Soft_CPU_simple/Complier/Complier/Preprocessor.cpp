#include "Preprocessor.h"

bool Preprocess(const char * file_input_name, const char * file_output_name)
{
    char * buff_input = nullptr;
    size_t buff_input_size = 0;
    buff_input_size = ReadFromFile(file_input_name, &buff_input);

    char ** strings = nullptr;
    size_t strings_amount = 0;
    strings_amount = ParseStringToStrings(buff_input, &strings);

    size_t cleaned_strings = 0;
    cleaned_strings = ClearStrings(&strings, strings_amount);

    if (!SaveStringsToFileCustom(file_output_name, strings, strings_amount)) {
        LOG_ERR_MESSAGE("can't save to file");
        free(buff_input);
        return false;
    }

    free(buff_input);
    return true;
}

size_t ClearStrings(char *** strings, size_t strings_amount) /// make it ! // this function deletes coments and so on 
{
    assert(strings != nullptr);
    size_t comments = DellComments(strings, strings_amount);
    size_t free_lines = DellClearlines(strings, strings_amount);
    return free_lines + comments;
}

size_t DellComments(char *** strings, size_t strings_amount)
{
    assert(*strings != nullptr);
    size_t comment_lines = 0;
    char * comment_start = nullptr;
    for (size_t i = 0; i < strings_amount; i++)
    {
        assert((*strings)[i] != nullptr);
        if (strchr((*strings)[i], '#') != nullptr)
        {
            comment_start = strchr((*strings)[i], '#');
            *comment_start = '\0';
            comment_lines++;
        }
    }
    return comment_lines;
}

size_t DellClearlines(char *** strings, size_t strings_amount)
{
    assert(*strings != nullptr);
    size_t clear_lines = 0;
    for (size_t i = 0; i < strings_amount; i++)
    {
        assert((*strings)[i] != nullptr);
        if (strlen((*strings)[i]) == 0 || *((*strings)[i]) == '\n')
        {
            clear_lines++;
            assert((*strings)[i] != nullptr);
            (*strings)[i] = nullptr;
        }
    }
    return clear_lines;
}
bool SaveStringsToFileCustom(const char * file_name, char ** strings, size_t strings_amount)
{
    assert(file_name != nullptr);
    assert(strings != nullptr);
    FILE* file = nullptr;
    const errno_t file_state = fopen_s(&file, file_name, "w");
    if (file_state || file == nullptr) {
        LOG_ERR("can't open file : ", file_name);
        return false;
    }

    for (size_t i = 0; i < strings_amount; i++) {
        if (strings[i] != nullptr) {
            fputs(strings[i], file);
            if (i != strings_amount - 1) { // last line without /n
                fputc('\n', file);
            }
        }
    }

    fclose(file);

    return true;
}