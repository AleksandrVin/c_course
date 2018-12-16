#pragma once

#define LOG_ERR( message , data ) \
    fprintf(stderr, "\n\tERROR:  %s : %s \n" , message , data)

#define LOG_ERR_NUM( message , data ) \
    fprintf(stderr, "\n\tERROR:  %s : %d \n" , message , data)