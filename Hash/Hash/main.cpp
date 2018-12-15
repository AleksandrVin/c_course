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

#define AMOUNT_OF_ROWS 500

#define MAX_STRING_SIZE 500

struct HashTable {
    int(*HashFunc)(char * string);
    List * hash_table[AMOUNT_OF_ROWS];
};


int GetHash_v1(char * strings);
int GetHash_v2(char * strings);
int GetHash_v3(char * strings);
int GetHash_v4(char * strings);
int GetHash_v5(char * strings);
int GetHash_v6(char * strings);

void Test(char ** strings, size_t amount_of_strings, int hash_func(char * string), size_t lists_amount, HashTable * hashTable);

void SaveResults(const char * file_output, HashTable * hashTable, size_t lists_amount);

void TestMethod(char ** strings, size_t amount_of_strings, int hash_func(char * string), const char * file_output);

void HashTableInsert(char * string, HashTable * hashtable);

int ConvertToIndex(int hashcode);

char * HashTableFind(char * string, HashTable * hashtable);

size_t ParseStringToStringsCustom(char * string_to_parse, char *** strings);

struct HashTable* HashTableCtor(int(*HashFunc)(char * string));

void HashTableDtor(HashTable * hashTable);


int main()
{
    char * buff;
    size_t size_of_buff = ReadFromFile(FILE_INPUT, &buff);

    char ** strings;
    size_t amount_of_strings = ParseStringToStringsCustom(buff, &strings);

    //PrintStrings(strings, amount_of_strings);

    TestMethod(strings, amount_of_strings, GetHash_v1, FILE_OUT_1);
    TestMethod(strings, amount_of_strings, GetHash_v2, FILE_OUT_2);
    TestMethod(strings, amount_of_strings, GetHash_v3, FILE_OUT_3);
    TestMethod(strings, amount_of_strings, GetHash_v4, FILE_OUT_4);
    TestMethod(strings, amount_of_strings, GetHash_v5, FILE_OUT_5);

    free(buff);
    free(strings);

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
    return (bit_sum >= 0) ? bit_sum : -bit_sum;
}

int GetHash_v4(char * strings)
{
    size_t lenght = strlen(strings);
    int bit_sum = 0;
    for (size_t i = 0; i < lenght; i++) {
        bit_sum += (strings[i] & 0x0F);
    } 
    return (bit_sum >= 0) ? bit_sum : -bit_sum;
}

int GetHash_v5(char * strings)
{
    size_t lenght = strlen(strings);
    int bit_sum = 0;
    for (size_t i = 0; i < lenght; i++) {
        bit_sum += (((~strings[i] & 0x0F) << 4) | ((~strings[i] & 0xF0) >> 4));
    }
    return (bit_sum >= 0) ? bit_sum : -bit_sum;
}
int GetHash_v6(char * strings)
{

    return 0;
}

void Test(char ** strings, size_t amount_of_strings, int hash_func(char * string), size_t lists_amount, HashTable * hashTable)
{
    for (size_t i = 0; i < amount_of_strings; i++) {
        HashTableInsert(strings[i], hashTable);
    }
}


void SaveResults(const char * file_output, HashTable * hashTable, size_t lists_amount)
{
    OpenFile(file_output, "w");
    fputs("hash value,amount of strings\n", file);
    for (size_t i = 0; i < lists_amount; i++) {
        fprintf_s(file, "%d,%d\n", i, hashTable->hash_table[i]->size);
    }
    fclose(file);
}

void TestMethod(char ** strings, size_t amount_of_strings, int hash_func(char *string), const char * file_output)
{
    HashTable * hashTable = HashTableCtor(hash_func);

    //performing test 
    Test(strings, amount_of_strings, hash_func, AMOUNT_OF_ROWS, hashTable);

    //save results
    SaveResults(file_output, hashTable, AMOUNT_OF_ROWS);

    HashTableDtor(hashTable);
}

void HashTableInsert(char * string, HashTable * hashtable)
{
    assert(string != nullptr);
    assert(hashtable != nullptr);
    int hash = hashtable->HashFunc(string);
    int index = ConvertToIndex(hash);
    ListInsert(hashtable->hash_table[index], string);
}

int ConvertToIndex(int hashcode)
{
    return hashcode % AMOUNT_OF_ROWS;
}

char * HashTableFind(char * string, HashTable * hashtable)
{
    assert(string != nullptr);
    assert(hashtable != nullptr);
    int hash = hashtable->HashFunc(string);
    int index = ConvertToIndex(hash);
    return (ListSearch(hashtable->hash_table[index], string)->data);
}

size_t ParseStringToStringsCustom(char * string_to_parse, char *** strings)
{
    size_t strings_amount = CountStrings(string_to_parse);
    *strings = (char**)calloc(strings_amount, sizeof(char*));
    char * buff_copy = string_to_parse;
    size_t current_string = 0;
    (*strings)[current_string] = buff_copy;
    current_string++;
    while (*buff_copy != '\0') {
        if (*buff_copy == '\n') {
            *buff_copy = '\0';
            if (*(buff_copy + 1) != '\0') {
                (*strings)[current_string] = buff_copy + 1;
                current_string++;
            }
        }
        if (*(buff_copy) == ' ') {
            *buff_copy = '\0';
        }
        buff_copy++;
    }
    return current_string;
}

HashTable* HashTableCtor(int(*HashFunc)(char * string))
{
    HashTable * hashTable = (HashTable*)calloc(1, sizeof(HashTable));
    hashTable->HashFunc = HashFunc;
    for (size_t i = 0; i < AMOUNT_OF_ROWS; i++) {
        (*hashTable).hash_table[i] = ListCtorDin();
    }
    return hashTable;
}

void HashTableDtor(HashTable * hashTable)
{
    for (size_t i = 0; i < AMOUNT_OF_ROWS; i++) {
        ListDtorDin(hashTable->hash_table[i]);
    }
    free(hashTable);
}
