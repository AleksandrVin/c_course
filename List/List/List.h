#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define BUFF_FOR_DOT_CALL 200


//works only with char*
#define LOG_ERR( message , data ) \
    fprintf(stderr, "\n\tERROR:  %s : %s \n" , message , data)
//works only with int*
#define LOG_ERR_NUM( message , data ) \
    fprintf(stderr, "\n\tERROR:  %s : %d \n" , message , data)


typedef int data_t;


struct Item {
    Item * prev;
    Item * next;
    data_t data;
};

struct List {
    size_t amount_of_elems = 0;
    Item * head = nullptr;
    Item * tail = nullptr;
    bool sorted = false;
    size_t size = 0;
};


List * ListCtorDin();
void ListDtorDin(List * list);

Item * ListInsert(List * list, data_t data);
bool ListDelete(List * list, data_t data);
bool ListRemove(List * list, Item * item);
//bool listPushBack(List * list, data_t * data_poiner);
//bool listPushFront(List * list, data_t * data_pointer);

Item * ListSearch(List * list, data_t data);

Item * ListCreateItem();
void listFreeElem(Item * item);

bool ListCheck(List * list);

void ListDump(List * list, const char * file_image_out, const char * image_file);

void ListDumpNode(FILE * file, Item * item , size_t number,const char * color);
