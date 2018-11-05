#include "Compiler.h"

size_t CompilerCompile(Compiler * progect, const char * file_to_read, const char * file_to_save)
{
    assert(progect != nullptr);
    //openinng files
    FILE* FILE_output = OpenFile(progect, file_to_save, "w");
    if (FILE_output == nullptr) {
        LOG_ERR("can't open file to save assembled program into file", file_to_save);
        return 0;
    }
    FILE* FILE_input = OpenFile(progect, file_to_read, "r");
    if (FILE_input == nullptr) {
        LOG_ERR("can't open file to read preprocessered program in file", file_to_read);
        return 0;
    }

    progect->size_of_buf_input = GetFileSize(FILE_input);
    progect->buf_input = (char*)calloc(progect->size_of_buf_input, sizeof(char));
    progect->size_of_buf_input = fread_s(progect->buf_input, progect->size_of_buf_input, sizeof(char), progect->size_of_buf_input, FILE_input);
    fclose(FILE_input);
    progect->string_amount = ParseToSrings(progect);

    free(progect->buf_input);
    progect->buf_input = nullptr;
    ClearStrings(progect);
    fclose(FILE_output);
    return progect->string_amount;
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
    /*   if (string_to_parse == "") {
           line_parsed->mode = MODE_FREE_LINE;
           return -1;
       }*/
    line_parsed->mode = MODE_ERR;
    return 0;
}

size_t ParseCommand(Command * com_to_parse)
{
    size_t args_parsed = 0;
    if (com_to_parse->mode == MODE_ACTION) {
        //args_parsed = ParseModeAction(com_to_parse);
    }
    return size_t();
}

size_t ParseModeAction(Command * com_to_parse)
{
#define DEF_CMD(name, num) \
if(strcmp(buf, #name) == 0) \
    fprintf(,"%d", CMD_##name);

    //#include "../Commands.h"

#undef DEF_CMD
    return size_t();
}

FILE * OpenFile(Compiler * progect, const char * file_to_open, const char * mode)
{
    assert(progect != nullptr);
    FILE* file;
    errno_t file_state = fopen_s(&file, file_to_open, mode);
    if (file_state) {
        LOG_ERR("can't open file : ", file_to_open);
        return nullptr;
    }
    return file;
}


