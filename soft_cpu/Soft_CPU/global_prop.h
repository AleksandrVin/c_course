/**
 /file 

 /brief stored global propertice of cpu

 /author Vinogradov Aleksandr
*/

#define COMMAND_NUMBER_BIT 0x01
#define COMMAND_REG_BIT 0x02
#define COMMAND_RAM_BIT 0x03


typedef unsigned char _cmd;
typedef int _data;

const size_t COMMAD_SIZE = sizeof(_cmd);
const size_t DATA_SIZE = sizeof(int);

enum Commands {
#define DEF_CMD(name, num ,code) CMD_##name = (num), 
#include "../Commands.h"
    CMD_MAX
#undef DEF_CMD
};