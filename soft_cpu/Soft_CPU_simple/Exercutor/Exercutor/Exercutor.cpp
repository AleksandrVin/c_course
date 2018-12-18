#include "Exercutor.h"

Process * CreateProcessDin(size_t id, const char * file)
{
    assert(file != nullptr);
    Process * process = (Process*)calloc(1, sizeof(Process));
    assert(process != nullptr);
    process->id = id;
    process->position = 0;
    process->size_of_buf_input = ReadFromFileBin(file, &process->buf_input);
    if (process->buf_input == nullptr) {
        LOG_ERR("can't load file to exercute", file);
        free(process);
        return nullptr;
    }
    process->stack = StackCtorDin();
    assert(process->stack != nullptr);
    process->position = 0;
    process->calls = StackCtorDin();
    assert(process->calls != nullptr);
    return process;
}

size_t DestructProcess(Process * process)
{
    assert(process != nullptr);
    size_t buff_size = process->size_of_buf_input;
    assert(process->buf_input != nullptr);
    free(process->buf_input);
    StackDtorDin(process->stack);
    StackDtorDin(process->calls);
    free(process);
    return buff_size;
}

size_t RunProces(Process * process)
{
    assert(process != nullptr);
    assert(process->buf_input != nullptr);
    size_t runs = 0;
    for (process->position = 0; process->position < process->size_of_buf_input; process->position++) {
        //printf("%hhX\n", (char)process->buf_input[process->position]); // for  debug
        if (!(process->position == 0 || process->running)) {
            break;
        }
        else {
            switch (process->buf_input[process->position])
            {
#define DEF_CMD(name, num, code) \
        case CMD_##name : \
            code \
            runs++; \
            break;

#include "Commands.h"

#undef DEF_CMD
            default:
                LOG_ERR_NUM("can't read command", process->position);
                break;

            }
        }
    }
    return runs;
}

size_t ReadNumber(char * data)
{
    assert(data != nullptr);
    size_t number = *(size_t*)data;
    return number;
}

_data ReadData(char * data)
{
    assert(data != nullptr);
    _data number = *(_data*)data;
    return number;
}

size_t ReadFromFileBin(const char * file_input, char ** string_for_result)
{
    assert(string_for_result != nullptr);
    assert(file_input != nullptr);
    ///opening file
    FILE* FILE_input = nullptr;
    const errno_t file_state = fopen_s(&FILE_input, file_input, "rb");
    if (file_state || FILE_input == nullptr) {
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
    *(*string_for_result + size_of_string_for_result) = '\0';

    return size_of_string_for_result;
}