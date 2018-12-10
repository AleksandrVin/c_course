/**
 /brief this is hash function test progect

 /author Aleksandr Vinogradov
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

#include "../../../Libs/MacrosLib/macros.h"

#include "../../../Libs/ListLib/ListChar.h"

#include "../../../Libs/FileReaderLib/ReaderLib.h"

#define FILE_INPUT "../data/dict_nex.txt"

#define FILE_OUT_1 "../data/hash1.csv"

#define FILE_OUT_2 "../data/hash2.csv"

#define FILE_OUT_3 "../data/hash3.csv"

#define FILE_OUT_4 "../data/hash4.csv"

#define FILE_OUT_5 "../data/hash5.csv"

#define FILE_OUT_6 "../data/hash6.csv"



#define AMOUNT_OF_ROWS 25

int GetHash_v1(char * strings);
int GetHash_v2(char * strings);
int GetHash_v3(char * strings);
int GetHash_v4(char * strings);
int GetHash_v5(char * strings);
int GetHash_v6(char * strings);

void Test(char ** strings, size_t amount_of_strings, int hash_func(char * string), size_t lists_amount, List ** lists);

void SaveResults(const char * file_output, List ** list, size_t lists_amount);

void TestMethod(char ** strings, size_t amount_of_strings, int hash_func(char * string), const char * file_output);


int main()
{
    char * buff;
    size_t size_of_buff = ReadFromFile(FILE_INPUT, &buff);

    char ** strings = nullptr;
    size_t amount_of_strings = ParseStringToStrings(buff, &strings);

    //free buff
    free(buff);

    TestMethod(strings, amount_of_strings, GetHash_v1, FILE_OUT_1);
    TestMethod(strings, amount_of_strings, GetHash_v2, FILE_OUT_2);
    TestMethod(strings, amount_of_strings, GetHash_v3, FILE_OUT_3);
    TestMethod(strings, amount_of_strings, GetHash_v4, FILE_OUT_4);
    TestMethod(strings, amount_of_strings, GetHash_v5, FILE_OUT_5);

    //free strings
    StringsMemClear(strings, amount_of_strings);

    return 0;
}

int GetHash_v1(char * strings)
{
    return 1;
}
int GetHash_v2(char * strings)
{
    return strlen(strings);
}

int GetHash_v3(char * strings)
{
    size_t lenght = strlen(strings);
    int bit_sum = 0;
    for (size_t i = 0; i < lenght; i++) {
        bit_sum += strings[i];
    }
    return bit_sum;
}

int GetHash_v4(char * strings)
{
    size_t lenght = strlen(strings);
    int bit_sum = 0;
    for (size_t i = 0; i < lenght; i++) {
        bit_sum += (strings[i] ^ strings[i] & 0x0F);
    }
    return bit_sum;
}

int GetHash_v5(char * strings)
{
    size_t lenght = strlen(strings);
    int bit_sum = 0;
    for (size_t i = 0; i < lenght; i++) {
        bit_sum += (((strings[i] ^ strings[i] & 0x0F) << 4) | ((strings[i] ^ strings[i] & 0xF0) >> 4));
    }
    return bit_sum;
}
int GetHash_v6(char * strings)
{

    return 0;
}

void Test(char ** strings, size_t amount_of_strings, int hash_func(char * string), size_t lists_amount, List ** list)
{
    for (size_t i = 0; i < amount_of_strings; i++) {
        int hash = hash_func(strings[i]) % lists_amount;
        ListInsert(list[hash], strings[i]);
    }
}


void SaveResults(const char * file_output, List ** list, size_t lists_amount)
{
    OpenFile(file_output, "w");
    fputs("hash value,amount of strings\n", file);
    for (size_t i = 0; i < lists_amount; i++) {
        fprintf_s(file, "%d,%d\n", i, list[i]->size);
    }
    fclose(file);
}

void TestMethod(char ** strings, size_t amount_of_strings, int hash_func(char *string), const char * file_output)
{
    List  * lists[AMOUNT_OF_ROWS];

    for (size_t i = 0; i < AMOUNT_OF_ROWS; i++) {
        lists[i] = ListCtorDin();
    }
    //performing test 
    Test(strings, amount_of_strings, hash_func, AMOUNT_OF_ROWS, lists);

    //save results
    SaveResults(file_output, lists, AMOUNT_OF_ROWS);
    //free lists
    for (size_t i = 0; i < AMOUNT_OF_ROWS; i++) {
        ListDtorDin(lists[i]);
    }
}
