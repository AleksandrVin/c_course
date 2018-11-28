#include "pch.h"

size_t LoadStrings(const char * file_name, char *** strings)
{
    FILE* file;
    errno_t file_state = fopen_s(&file, file_name, "r");
    if (file_state) {
        LOG_ERR("can't open file : ", file_name);
        return 0;
    }

    size_t size_of_buf_input = GetFileSize(file);
    char * buf_input = (char*)calloc(size_of_buf_input, sizeof(char));
    size_of_buf_input = fread_s(buf_input, size_of_buf_input, sizeof(char), size_of_buf_input, file);
    fclose(file);

    size_t string_amount = ParseToSrings(buf_input, size_of_buf_input, strings);

    return string_amount;
}

Node * LoadTreeFromFile(const char * file_name, size_t string_amount)
{
    FILE* file;
    errno_t file_state = fopen_s(&file, file_name, "r");
    if (file_state) {
        LOG_ERR("can't open file : ", file_name);
        return 0;
    }

    size_t size_of_buf_input = GetFileSize(file);
    char * buf_input = (char*)calloc(size_of_buf_input, sizeof(char));
    size_of_buf_input = fread_s(buf_input, size_of_buf_input, sizeof(char), size_of_buf_input, file);
    fclose(file);

    return ResolveNode(buf_input);
}

int ParseToSrings(char * buf_input, size_t size_of_buf_input, char *** strings)
{
    int string_counter = CountStrings(buf_input, size_of_buf_input);
    *strings = (char**)calloc(string_counter, sizeof(char*));
    size_t string_amount = 0;
    char * buf_copy = buf_input;
    char * buf_end = buf_copy + size_of_buf_input;
    char * last_string = buf_copy;
    for (buf_copy; buf_copy < buf_end; buf_copy++)
    {
        if (*buf_copy == '\n') {
            (*strings)[string_amount] = (char*)calloc(buf_copy - last_string + 1, sizeof(char));
            size_t i = 0;
            for (last_string; last_string < buf_copy; last_string++) {
                (*strings)[string_amount][i] = *last_string;
                i++;
            }
            (*strings)[string_amount][i] = '\0';
            string_amount++;
            last_string = buf_copy + 1;
        }
    }
    if (last_string != buf_copy + 1) {
        (*strings)[string_amount] = (char*)calloc(buf_end - last_string + 1, sizeof(char));
        size_t i = 0;
        for (last_string; last_string < (buf_end); last_string++) {
            (*strings)[string_amount][i] = *last_string;
            i++;
        }
        (*strings)[string_amount][i] = '\0';
        string_amount++;
    }
    return string_amount;
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

size_t GetFileSize(FILE* file_to_seek)
{
    fseek(file_to_seek, 0, SEEK_END); // seek to end 
    size_t file_size = ftell(file_to_seek); // gets end position
    fseek(file_to_seek, 0, SEEK_SET); // seek to start
    return file_size;
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

Node * ResolveNode(const char * buff)
{
    assert(buff != nullptr);

    size_t current = 0;
    if (buff[current] == '(') {
        Node * node = (Node*)calloc(1, sizeof(Node));
        sscanf(buff,"%d", &node->data);
        if(don)
        
    }
    return nullptr;
}

Node * ReadNode(const char * buff, size_t position)
{
    assert(buff != nullptr);

    if (buff[position] == '(') {
        Node * node = (Node*)calloc(1, sizeof(Node));
        size_t number = 0;
        size_t pos = ReadNumberCountsDoNotUseIt(buff, position, &number);
        node->data = number;
        position += pos;
        if(buff[position+1] == '('
    }
}

size_t Pow(size_t number, size_t powing)
{
    size_t result = number;
    if (powing == 0) {
        return 1;
    }
    for (powing; powing > 1; powing--) 
    {
        result *= number;
    }
    return result;
}

size_t ReadNumberCountsDoNotUseIt(const char * buff, size_t position,size_t * number)
{
    assert(buff != nullptr);

    *number = 0;
    size_t pos = 1;
    char current = buff[position + pos];
    while (isdigit(current)) {
        *number += (buff[position + pos] - '0')*Pow(10, pos);
        pos++;
    }
    return pos;
}