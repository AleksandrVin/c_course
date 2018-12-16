/**
 /file 

 /brief stored global propertice of cpu

 /author Vinogradov Aleksandr
*/

//comand rules
#define COMMAND_NUMBER_BIT 0x01
#define COMMAND_REGISTER_BIT 0x02
#define COMMAND_RAM_BIT 0x03


typedef unsigned char _cmd;
typedef int _data;

const size_t COMMAD_SIZE = sizeof(_cmd);
const size_t DATA_SIZE = sizeof(int);

enum Commands {
#define DEF_CMD(name, num ,code) CMD_##name = (num), 
#include "Commands.h"
    CMD_MAX
#undef DEF_CMD
};

enum Registers {
#define DEF_REG(name, num) REG_##name = (num), 
#include "Registers.h"
    REG_MAX 
#undef DEF_REG
};
//update when change registers
#define REGISTERS_AMOUNT 4