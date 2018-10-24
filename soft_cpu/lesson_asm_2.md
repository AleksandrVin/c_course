# Расширяем функционал ассемблера

мы имеем 3 программы:

1. Ассемблер
2. Процессор
3. Дизассемблер

## Что мы имеем общего

**enum** со списком команд и их кодов

### Получается нам нудно сделать это в одном месте

#### Для начала посмотрим на пример нашего enum

```c
enum Comands
{
    CMD_PUSH = 1,
    CMD_POP = 2,
    CDM_ADD = 3,
}
```

посмотрим на нашу прогу(условно)

assembler

```c
char buf[..] = "";
fscanf(f,"%s", buf);
if(strcmp(buf,"push") == 0)
    fprintf(f2,"%d", CMD_PUSH);
...
else if(strcmp(buf,"add") == 0)
    fprintf(f2,"%d", CMD_ADD);
```

processor

```c
switch(code[ip])
{
    case CMD_PUSH ...;
    case CMD_POP ...;
    case CMD_ADD:
       StrPush(stk, StrPop(stk) + stkPop(stk));
       break;
}
```

#### Очевидно что это копипаст, который можно сделать лучше

давайте попробуем сделать так

```c
#define DEF_CMD CMD_PUSH = 1;
```

### Давайте создадим файл **commamds.h**

```c
//commands.h
DEF_CMD (PUSH,1)
DEF_CMD (POP,2)
DEF_CMD (ADD,3)
DEF_CMD (SUB,4)


```

тогда наш **enum** будет выглядеть так

```c
enum Commands
{
    #define DEF_CMD(name, num) CMD_##name = (num), // ## Это указание предпроцессору "приклеить имя name к CMD_
    #include "commands.h"
    CMD_MAX
    #undef DEF_CMD
};
``` 

таким образом файл commands.h развернется по нашему правилу в дефайн

наша прога станет похожа на это

```c
//asm.h
char buf[] = "";
fscanf(f, "%s", buf);
#define DEF_CMD(name, num) \
if(strcmp(buf, #name) == 0) \
    fprintf(f2,"%d", CMD_##name);

#include "commands.h"

#undef DEF_CMD
```

изменим commands.h в формат с 3 аргументами 

```c
//commands.h
DEF_CMD(SUB, 4
{
    double a = StrPop(stk), b = StrPop(stk);
    StkPush(stk, a - b);
})

DEF_CMD (ADD,3,
{
    PUSH(POP+POP);
})
```

теперь можно процессор переписать так

```c
//processor.h
switch(code[ip])
{
    #define DEF_CMD(name, num, code) \
        case CMD_##name: code; break;
    #include "commands.h"
}
```

то что мы сделали - есть по сути **DSL**

### Немного магии с консолью

```bash
g++ -E main.cpp > wtf.txt // эта штука раскроет define и запишет в файл whf.txt
```

>_внимание_ необходимо закомменировать стандартные либы, иначе мы получим очень много строк кода

> нужно добавить комменты к блокам автогенерации, что их нельзя менять, а нужно трогать файл конфигурации