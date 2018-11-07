#pragma once


//command modes
#define MODE_ACTION 1
#define MODE_NUMBER 2
#define MODE_REGISTER 3
#define MODE_RAM 4 
#define MODE_ERR 0
#define MODE_FREE_LINE 10

#define MAX_LENGTH_OF_COMMAND 10


//works only with char*
#define LOG_ERR( message , data ) \
    fprintf(stderr, "\n\tERROR:  %s : %s \n" , message , data)
//works only with int*
#define LOG_ERR_NUM( message , data ) \
    fprintf(stderr, "\n\tERROR:  %s : %d \n" , message , data)

