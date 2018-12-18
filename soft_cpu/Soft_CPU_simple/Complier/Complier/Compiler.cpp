#include "Compiler.h"

bool Compiler(const char * file_input_name, const char * file_output_name, Label * labels, bool label_set, size_t * labels_amount)
{
    char * buff_input = nullptr;
    size_t buff_input_size = 0;
    buff_input_size = ReadFromFile(file_input_name, &buff_input);

    char ** strings = nullptr;
    size_t strings_amount = 0;
    strings_amount = ParseStringToStrings(buff_input, &strings);

    //bool save_status = SaveStringsToFile(file_output_name, strings, strings_amount);
    //if (!save_status) {
    //    LOG_ERR_MESSAGE("can't save complied file");
    //    return false;
    //}

    FILE * FILE_output = nullptr;
    errno_t file_state = fopen_s(&FILE_output, file_output_name, "wb");
    if (file_state || FILE_output == nullptr) {
        LOG_ERR_MESSAGE("can't open file to save result");
        return false;
    }

    size_t current_position = 0;
    for (size_t i = 0; i < strings_amount; i++) {
        Command command_now;
        size_t args_n = ParseString(strings[i], &command_now);
        if (args_n == 0) {
            LOG_ERR_NUM("error in line = ", i);
            return 0;
        }
        bool recognised = false;
        if (command_now.mode == MODE_NUMBER) {
#define DEF_CMD(name, num , code) \
            if(strcmp(command_now.command_raw, #name) == 0){ \
                putc(CMD_##name, FILE_output); \
                putc(COMMAND_NUMBER_BIT,FILE_output); \
                SaveData(FILE_output, command_now.number); \
                current_position += COMMAD_SIZE + MODIFIRE_SIZE + DATA_SIZE; \
                recognised = true;  \
            }
#include "Commands.h"

#undef DEF_CMD

        }


        if (command_now.mode == MODE_ACTION) {
#define DEF_CMD(name, num , code) \
            if(strcmp(command_now.command_raw, #name) == 0){ \
                putc(CMD_##name , FILE_output); \
                current_position += COMMAD_SIZE; \
                recognised = true;  \
            } 
#include "Commands.h"

#undef DEF_CMD
        }


        if (command_now.mode == MODE_REGISTER) {
#define DEF_CMD(name, num , code) \
            if(strcmp(command_now.command_raw, #name) == 0){ \
                putc(CMD_##name , FILE_output); \
                putc(COMMAND_REGISTER_BIT, FILE_output); \
                SaveNumber(FILE_output,CompareRegister(command_now.number_raw)); \
                current_position += INDEX_SIZE + MODIFIRE_SIZE + COMMAD_SIZE; \
                recognised = true;  \
            }
#include "Commands.h"

#undef DEF_CMD

        }

        if (command_now.mode == MODE_RAM) {
#define DEF_CMD(name, num , code) \
            if(strcmp(command_now.command_raw, #name) == 0){ \
                putc(CMD_##name , FILE_output); \
                putc(COMMAND_RAM_BIT, FILE_output); \
                SaveNumber(FILE_output,command_now.index); \
                current_position += INDEX_SIZE + MODIFIRE_SIZE + COMMAD_SIZE; \
                recognised = true;  \
            }
#include "Commands.h"

#undef DEF_CMD

        }

        if (command_now.mode == MODE_LABEL) {
            if (!label_set && *labels_amount < MAX_AMOUNT_OF_LABELS) {
                strcpy_s(labels[*labels_amount].label, MAX_LENGTH_OF_COMMAND, command_now.command_raw);
                (labels[*labels_amount]).row = current_position;
                *labels_amount = *labels_amount + 1;
            }
            recognised = true;
        }

        if (command_now.mode == MODE_CONDITION) {
#define DEF_CMD(name, num , code) \
            if(strcmp(command_now.command_raw, #name) == 0){ \
                putc(CMD_##name , FILE_output); \
                if(label_set){ \
                    _index jmp_pos = SearchLabel(command_now.number_raw,labels,*labels_amount); \
                    if (jmp_pos != (_index)(-1)) { \
                        SaveNumber(FILE_output,jmp_pos); \
                    } \
                    else { \
                        puts("no label find"); \
                    } \
                } \
                else { \
                    SaveNumber(FILE_output, (_index)-1); \
                } \
                current_position += INDEX_SIZE + COMMAD_SIZE; \
                recognised = true;  \
            }
#include "Commands.h"

#undef DEF_CMD

        }


        if (!recognised) {
            LOG_ERR_NUM("error in code, line = ", (i + 1));
        }
    }

    fclose(FILE_output);
    return true;
}


size_t ParseString(const char * string_to_parse, Command * line_parsed)
{
    assert(line_parsed != nullptr);
    assert(string_to_parse != nullptr);
    if (sscanf_s(string_to_parse, ":%s", line_parsed->command_raw, MAX_LENGTH_OF_COMMAND) == 1) {
        line_parsed->mode = MODE_LABEL;
        return 1;
    }
    if (sscanf_s(string_to_parse, "%9s %lf", line_parsed->command_raw, MAX_LENGTH_OF_COMMAND, &(line_parsed->number)) == 2) { //   , &number, (unsigned)_countof(line), (unsigned)sizeof(int)) == 2) { // format like {push 10}
        line_parsed->mode = MODE_NUMBER;
        return 2;
    }
    if (sscanf_s(string_to_parse, "%9s [%zu]", line_parsed->command_raw, MAX_LENGTH_OF_COMMAND, &(line_parsed->index)) == 2) { // format like {push [10]}
        line_parsed->mode = MODE_RAM;
        return 2;
    }
    if (sscanf_s(string_to_parse, "%9s :%s", line_parsed->command_raw, MAX_LENGTH_OF_COMMAND, line_parsed->number_raw, MAX_LENGTH_OF_COMMAND) == 2) { //   , &number, (unsigned)_countof(line), (unsigned)sizeof(int)) == 2) { // format like jmp 10
        line_parsed->mode = MODE_CONDITION;
        return 2;
    }
    if (sscanf_s(string_to_parse, "%9s%9s", line_parsed->command_raw, MAX_LENGTH_OF_COMMAND, line_parsed->number_raw, MAX_LENGTH_OF_COMMAND) == 2) { // format like {push ax}
        line_parsed->mode = MODE_REGISTER;
        return 2;
    }
    if (sscanf_s(string_to_parse, "%9s", line_parsed->command_raw, MAX_LENGTH_OF_COMMAND) == 1) { // format like {add}
        line_parsed->mode = MODE_ACTION;
        return 1;
    }
    line_parsed->mode = MODE_ERR;
    return 0;
}

size_t SaveNumber(FILE * file, _index number)
{
    assert(file != nullptr);
    return fwrite(&number, INDEX_SIZE, 1, file);
}

size_t SaveData(FILE * file, _data number)
{
    assert(file != nullptr);
    return (size_t)fwrite(&number, DATA_SIZE, 1, file);
}

_index CompareRegister(const char * register_raw)
{
#define DEF_REG(name, num) \
            if(strcmp(register_raw, #name) == 0){ \
                return REG_##name; \
            }

#include "Registers.h"

#undef DEF_REG
    return 0;
}

_index SearchLabel(const char * string_to_search, Label * labels, size_t labels_amount = 0)
{
    for (size_t i = 0; i <= labels_amount; i++)
    {
        if (strcmp(labels[i].label, string_to_search) == 0) {
            return labels[i].row;
        }
    }
    return (_index)-1;
}