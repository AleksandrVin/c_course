/**
 /file

 /brief commands declaration for cpu

 /author Vinogradov Aleksandr
*/

DEF_CMD(init, 0x10, { break; })
DEF_CMD(push, 0x20, { StackPush(process->stack, ReadNumber(&process->buf_input[i + 1])); })
DEF_CMD(pop, 0x30, { break; })
DEF_CMD(add, 0x40, { StackPush(process->stack, StackPop(process->stack) + StackPop(process->stack)); })
DEF_CMD(sub, 0x50, { break; })
DEF_CMD(jmp, 0x60, { break; })
DEF_CMD(out, 0x70, { printf("%d",StackPop(process->stack)); })
DEF_CMD(end, 0xB0, { break; })
DEF_CMD(mem, 0xC0, { break; })