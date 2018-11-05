#include "Compiler.h"

size_t CompilerCompile(Compiler * progect, const char * file_to_read, const char * file_to_save)
{
    assert(progect != nullptr);
    //openinng files
    FILE* FILE_output = OpenFile(progect, file_to_save, "wb");
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

    for (size_t i = 0; i < progect->string_amount; i++) {
        Command command_now;
        size_t args_n = ParseString(progect, progect->strings[i], &command_now);
        if (args_n == 0) {
            LOG_ERR("error in line = ", i);
            return 0;
        }
        bool recognised = false;
        if (command_now.mode == MODE_NUMBER) {
#define DEF_CMD(name, num) \
            if(strcmp(command_now.command_raw, #name) == 0){ \
                putc(CMD_##name , FILE_output); \
            fprintf_s(FILE_output, "%d", command_now.number); \
recognised = true;  \
            }

#include "../Commands.h"

#undef DEF_CMD
        }
        else if (command_now.mode == MODE_ACTION) {
#define DEF_CMD(name, num) \
            if(strcmp(command_now.command_raw, #name) == 0){ \
                putc(CMD_##name , FILE_output); \
recognised = true;  \
            } 

#include "../Commands.h"

#undef DEF_CMD
        }

        if (!recognised) {
            LOG_ERR_NUM("error in code, line = ", i + 1);
        }
    }


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

    if (sscanf_s(string_to_parse, "%9s %d", line_parsed->command_raw, MAX_LENGTH_OF_COMMAND, &(line_parsed->number), 1) == 2) { //   , &number, (unsigned)_countof(line), (unsigned)sizeof(int)) == 2) { // format like {push 10}
        line_parsed->mode = MODE_NUMBER;
        return 2;
    }
    if (sscanf_s(string_to_parse, "%s[%d]", line_parsed->command_raw, MAX_LENGTH_OF_COMMAND, &(line_parsed->number), 1) == 2) { // format like {push [10]}
        line_parsed->mode = MODE_RAM;
        return 2;
    }
    if (sscanf_s(string_to_parse, "%s%s", line_parsed->command_raw, MAX_LENGTH_OF_COMMAND, line_parsed->number_raw, 1) == 2) { // format like {push ax}
        line_parsed->mode = MODE_REGISTER;
        return 2;
    }
    if (sscanf_s(string_to_parse, "%s", line_parsed->command_raw, MAX_LENGTH_OF_COMMAND) == 1) { // format like {add}
        line_parsed->mode = MODE_ACTION;
        return 1;
    }
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


