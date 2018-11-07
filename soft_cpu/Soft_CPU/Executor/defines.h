#pragma once

#define LOG_ERR( message , data ) \
    fprintf(stderr, "\n\tERROR:  %s : %s \n" , message , data)