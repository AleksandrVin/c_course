#pragma once

#include <iostream>

#if !defined(NDEBUG)

//#define PRINTF printf

//print value of someting
#define $( x ) std::cout << "#" << x << " = " << ( x );

//unittest what checkes 2 values 
#define UNITTEST( what, ref ) \
   if((what) != (ref)) printf("\r[%.*s|%.*s] // FAILED: %d = %d , expected: %s = %d , line: %d in file: %s\n", passed , "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" \
       , total_passed , "--------------------------------------------------------------------------------------", (what), (ref) , #what ,(ref) , __LINE__ , __FILE__); \
   else printf("[%.*s|%.*s]\r", passed , "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" \
       , total_passed , "--------------------------------------------------------------------------------------");



#else
//#define PRINTF  ;
#define UNITTEST ;

#endif

