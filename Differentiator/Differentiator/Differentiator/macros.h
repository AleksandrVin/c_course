

#pragma once


//works only with char*
#define LOG_ERR_MESSAGE( message ) \
    fprintf(stderr, "\n\tERROR:  %s \n" , message)

//works only with char*
#define LOG_ERR( message , data ) \
    fprintf(stderr, "\n\tERROR:  %s : %s \n" , message , data)

//works only with int*
#define LOG_ERR_NUM( message , data ) \
    fprintf(stderr, "\n\tERROR:  %s : %d \n" , message , data)