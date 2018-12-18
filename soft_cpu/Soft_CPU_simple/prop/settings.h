#define MODE_ACTION 1
#define MODE_NUMBER 2
#define MODE_REGISTER 3
#define MODE_RAM 4 
#define MODE_LABEL 5
#define MODE_CONDITION 6
#define MODE_ERR 0
#define MODE_FREE_LINE 10

#define COMMAND_NUMBER_BIT 0x01
#define COMMAND_REGISTER_BIT 0x02
#define COMMAND_RAM_BIT 0x03


constexpr auto MAX_LENGTH_OF_COMMAND = 10;

constexpr auto MAX_AMOUNT_OF_LABELS = 100;

typedef unsigned char _cmd;
typedef double _data;
typedef size_t _index;

const size_t COMMAD_SIZE = sizeof(_cmd);
const size_t DATA_SIZE = sizeof(_data);
const size_t INDEX_SIZE = sizeof(size_t);

constexpr auto MODIFIRE_SIZE = 1;

constexpr auto COMMAND_SIZE = 1;

constexpr auto REGISTERS_AMOUNT = 8;

constexpr auto RAM_AMOUNT = 1000;

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