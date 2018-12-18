/**
 /file

 /brief commands declaration for cpu

 /author Vinogradov Aleksandr
*/

DEF_CMD(init, 0x10, {
    process->running = true;
    })
DEF_CMD(end, 0x11, {
    process->running = false;
    })
DEF_CMD(test, 0x12, { puts("test print"); })
DEF_CMD(push, 0x20, {
    switch (process->buf_input[process->position + MODIFIRE_SIZE])
    {
        case COMMAND_NUMBER_BIT:
            StackPush(process->stack, ReadData(&(process->buf_input[process->position + MODIFIRE_SIZE + MODIFIRE_SIZE])));
            process->position += DATA_SIZE + MODIFIRE_SIZE; // this is main for buffer 
            break;
        case COMMAND_REGISTER_BIT:
            StackPush(process->stack, process->registers[ReadNumber(&(process->buf_input[process->position + MODIFIRE_SIZE + MODIFIRE_SIZE]))]);
            process->position += DATA_SIZE + MODIFIRE_SIZE; // this is main for buffer 
            break;
        case COMMAND_RAM_BIT:
            StackPush(process->stack, process->ram[ReadNumber(&(process->buf_input[process->position + MODIFIRE_SIZE + MODIFIRE_SIZE]))]);
            process->position += DATA_SIZE + MODIFIRE_SIZE; // this is main for buffer 
            break;
        default:
            LOG_ERR_NUM("can't do this with this command mode in push", process->buf_input[process->position + MODIFIRE_SIZE]);
            exit(-1);
            break;
    }
})
DEF_CMD(pop, 0x21, {
    switch (process->buf_input[process->position + MODIFIRE_SIZE])
                {
                case COMMAND_REGISTER_BIT:
                    process->registers[ReadNumber(&(process->buf_input[process->position + MODIFIRE_SIZE + MODIFIRE_SIZE]))] = StackPop(process->stack);
                    process->position += DATA_SIZE + MODIFIRE_SIZE; // this is main for buffer 
                    break;
                case COMMAND_RAM_BIT:
                    process->ram[ReadNumber(&(process->buf_input[process->position + MODIFIRE_SIZE + MODIFIRE_SIZE]))] = StackPop(process->stack);
                    process->position += DATA_SIZE + MODIFIRE_SIZE; // this is main for buffer 
                    break;
                default:
                    LOG_ERR_NUM("can't do this mode of action in pop command", process->buf_input[process->position + MODIFIRE_SIZE]);
                    exit(-1);
                    break;
                }
})
DEF_CMD(add, 0x30, {
      StackPush(process->stack, StackPop(process->stack) + StackPop(process->stack));
      })
DEF_CMD(sub, 0x31, { 
      _data first = StackPop(process->stack);
      _data second = StackPop(process->stack);
      StackPush(process->stack, second - first); 
    })
DEF_CMD(mul, 0x32, {
      StackPush(process->stack, StackPop(process->stack) * StackPop(process->stack));
      })
DEF_CMD(sin, 0x35, {
      StackPush(process->stack, sin(StackPop(process->stack)));
      })
DEF_CMD(cos, 0x36, {
      StackPush(process->stack, cos(StackPop(process->stack)));
      })
DEF_CMD(div, 0x33, {
      _data first = StackPop(process->stack);
      _data second = StackPop(process->stack);
      StackPush(process->stack, second / first);
      })
DEF_CMD(sqrt, 0x34, {
      StackPush(process->stack, (_data)sqrt(StackPop(process->stack)));
      })
DEF_CMD(jmp, 0x60, { process->position = (size_t)ReadNumber(&(process->buf_input[process->position + MODIFIRE_SIZE])) - MODIFIRE_SIZE; })
DEF_CMD(call, 0x61, {
          StackPush(process->calls,(int)process->position);
          process->position = (size_t)ReadNumber(&(process->buf_input[process->position + MODIFIRE_SIZE])) - MODIFIRE_SIZE;
      })
DEF_CMD(ret, 0x62, {
          process->position = (size_t)(StackPop(process->calls)) + DATA_SIZE;
      })
DEF_CMD(ja, 0x63, {
          size_t row = (size_t)ReadNumber(&(process->buf_input[process->position + MODIFIRE_SIZE])) - MODIFIRE_SIZE;
          if (StackPop(process->stack) < StackPop(process->stack)) {
              process->position = row;
          }
          else {
              process->position += DATA_SIZE;
          }
       })
DEF_CMD(jb, 0x64, {
          size_t row = (size_t)ReadNumber(&(process->buf_input[process->position + MODIFIRE_SIZE])) - MODIFIRE_SIZE;
          if (StackPop(process->stack) > StackPop(process->stack)) {
              process->position = row;
          }
          else {
              process->position += DATA_SIZE;
          }
       })
DEF_CMD(je, 0x65, {
          size_t row = (size_t)ReadNumber(&(process->buf_input[process->position + MODIFIRE_SIZE])) - MODIFIRE_SIZE;
          if (StackPop(process->stack) == StackPop(process->stack)) {
              process->position = row;
          } 
          else {
              process->position += DATA_SIZE;
          }
        })
DEF_CMD(out, 0x70, { printf("%lf\n",StackPop(process->stack)); })