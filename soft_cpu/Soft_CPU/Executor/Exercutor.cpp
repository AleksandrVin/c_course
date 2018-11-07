#include "Exercutor.h"

size_t RunProces(Process * process)
{
    assert(process != nullptr);
    process->running = true;
    assert(process->buf_input != nullptr);
    size_t runs = 0;

    
    for(size_t i = 0;i < process->size_of_buf_input;i++) {
        switch (process->buf_input[i])
        {
#define DEF_CMD(name, num, code) \
        case CMD_##name : \
            code; \
runs++; \
            break;

#include "../Commands.h"

#undef DEF_CMD
        default :
            break;

        }
    }
    process->running = false;
    return runs;
}

Process * CreateProcessDin(size_t id, const char * file)
{
    Process * process = (Process*)calloc(1, sizeof(Process));
    FILE * FILE_reading = OpenFile(file, "rb");
    size_t file_size = GetFileSize(FILE_reading);
    process->buf_input = (char*)calloc(process->size_of_buf_input, sizeof(char));
    process->size_of_buf_input = fread_s(process->buf_input, process->size_of_buf_input, sizeof(char), process->size_of_buf_input, FILE_reading);
    fclose(FILE_reading);

    process->stack = StackCtorDin();

    process->position = 0;
    return process;
}

size_t DestructProcess(Process * process)
{
    assert(process != nullptr);
    size_t buff_size = process->size_of_buf_input;
    free(process->buf_input);
    free(process);
    return buff_size;
}


FILE * OpenFile(const char * file_to_open, const char * mode)
{
    FILE* file;
    errno_t file_state = fopen_s(&file, file_to_open, mode);
    if (file_state) {
        LOG_ERR("can't open file : ", file_to_open);
        return nullptr;
    }
    return file;
}

size_t GetFileSize(FILE* file_to_seek)
{
    fseek(file_to_seek, 0, SEEK_END); // seek to end 
    size_t file_size = ftell(file_to_seek); // gets end position
    fseek(file_to_seek, 0, SEEK_SET); // seek to start
    return file_size;
}

int ReadNumber(char * data)
{
    int number = 0;
    for (size_t i = 0; i < DATA_SIZE; i++) {
        number = number | data[i];
        number = number << 8;
    }
    return number;
}
