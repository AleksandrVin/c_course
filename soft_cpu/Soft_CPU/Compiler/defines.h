#pragma once


//command modes
#define MODE_ACTION 1
#define MODE_NUMBER 2
#define MODE_REGISTER 3
#define MODE_RAM 4 
#define MODE_ERR 0
#define MODE_FREE_LINE 10

#define MAX_LENGTH_OF_COMMAND 10

typedef unsigned char cmd;
typedef int data;

const size_t COMMAD_SIZE = sizeof(cmd);
const size_t DATA_SIZE = sizeof(int);

//works only with char*
#define LOG_ERR( message , data ) \
    fprintf(stderr, "\n\tERROR:  %s : %s" , message , data)

enum Commands {
    #define DEF_CMD(name, num) CMD_##name = (num), 
    #include "../Commands.h"
    CMD_MAX
    #undef DEF_CMD
};