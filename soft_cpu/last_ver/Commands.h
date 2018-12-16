/**
 /file

 /brief commands declaration for cpu

 /author Vinogradov Aleksandr
*/

DEF_CMD(init, 0x10, { 
    process->running = true;
})
DEF_CMD(push, 0x20, {
    switch (process->buf_input[process->position + 1])
    {
    case COMMAND_NUMBER_BIT:
        StackPush(process->stack, ReadNumber(&(process->buf_input[process->position + 2])));
        process->position += 5; // this is main for buffer 
        break;
    case COMMAND_REGISTER_BIT:
        StackPush(process->stack, process->registers[ReadNumber(&(process->buf_input[process->position + 2]))]);
        process->position += 5; // this is main for buffer 
        break;
    case COMMAND_RAM_BIT:
        StackPush(process->stack, process->ram[ReadNumber(&(process->buf_input[process->position + 2]))]);
        process->position += 5; // this is main for buffer 
        break;
    default:
        LOG_ERR_NUM("can't do this with this command mode in push", process->buf_input[process->position + 1]);
        exit(1);
        break;
    }
})
DEF_CMD(pop, 0x30, { 
    switch(process->buf_input[process->position + 1])
        {
        case COMMAND_REGISTER_BIT:
            process->registers[ReadNumber(&(process->buf_input[process->position + 2]))] = StackPop(process->stack);
            process->position += 5; // this is main for buffer 
            break;
        case COMMAND_RAM_BIT:
            process->ram[ReadNumber(&(process->buf_input[process->position + 2]))] = StackPop(process->stack);
            process->position += 5; // this is main for buffer 
            break;
        default:
            LOG_ERR_NUM("can't do this mode of action in pop command", process->buf_input[process->position + 1]);
            exit(1);
            break;
        }
})
DEF_CMD(add, 0x40, { 
        StackPush(process->stack, StackPop(process->stack) + StackPop(process->stack)); 
})
DEF_CMD(sub, 0x50, { StackPush(process->stack, StackPop(process->stack) - StackPop(process->stack)); })
DEF_CMD(jmp, 0x60, { break; })
DEF_CMD(out, 0x70, { printf("%d",StackPop(process->stack)); })
DEF_CMD(end, 0xB0, { process->running = false; })
DEF_CMD(mem, 0xA0, {
    switch (process->buf_input[process->position + 1])
    {
    case COMMAND_NUMBER_BIT:
        process->ram = (int*)_recalloc(process->ram,ReadNumber(&(process->buf_input[process->position + 2])),DATA_SIZE);
        if (process->ram == nullptr) {
            LOG_ERR_NUM("can't calloc ram for ", ReadNumber(&(process->buf_input[process->position + 2])));
            exit(1);
        }
        LOG_ERR("err", "rrr");
        process->ram_ammount = ReadNumber(&(process->buf_input[process->position + 2]));
        process->position += 5; // this is main for buffer 
        break;
    default:
        LOG_ERR_NUM("Can't read mode for mem command", process->buf_input[process->position + 1]);
        exit(1);
        break;
    }
    })
    DEF_CMD(test, 0x00, { break; })