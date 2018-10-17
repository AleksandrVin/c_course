#pragma once

#include <iostream>

#if !defined(NDEBUG)

//#define PRINTF printf

//print value of someting
#define $( x ) std::cout << "#" << x << " = " << ( x );

//unittest what checkes 2 values 
#define UNITTEST( what, ref ) \
   if((what) != (ref)){ printf("\r[%.*s|%.*s] // FAILED: %d = %d , expected: %s = %d , line: %d in file: %s\n from function: %s", passed , "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" \
       , total_passed , "--------------------------------------------------------------------------------------", (what), (ref) , #what ,(ref) , __LINE__ , __FILE__, __FUNCSIG__); system("Color 6F");} \
   else printf("[%.*s|%.*s]\r", passed , "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" \
       , total_passed , "--------------------------------------------------------------------------------------");

#define UNITTEST_FAST( what, ref ) \
   if((what) != (ref)){ printf("\r[%.*s|%.*s] // FAILED: %d = %d , expected: %s = %d , line: %d in file: %s\n from function: %s", passed , "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" \
       , total_passed , "--------------------------------------------------------------------------------------", (what), (ref) , #what ,(ref) , __LINE__ , __FILE__, __FUNCSIG__); system("Color 6F");} \


#else
//#define PRINTF  ;
#define UNITTEST ;

#define UNITTEST_FAST ;

#endif

