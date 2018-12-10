
/**
 \brief header for list library

 \authors Vinogradov Aleksandr

 @note 
*/
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

/**
     /brief Create New list

     /return pointer to list
*/
List * ListCtorDin();
/**
     /brief delete list 

     /param[in] list pointer to list to delete

     /return void
*/
void ListDtorDin(List * list);

Item * ListInsert(List * list, data_t data);

/**
     /brief remove element with data from list

     /param[in]  list pointer to list 
     /param[in]  data data to remove from list

     /return true is succes
*/
bool ListDelete(List * list, data_t data);
/**
     /brief remove element with pinter to item in list

     /param[in]  list poiner to list
     /param[in]  item pinter to item in list to remove

     /return true is succes
*/
bool ListRemove(List * list, Item * item);

Item * ListSearch(List * list, data_t data);

Item * ListCreateItem();

void listFreeElem(Item * item);

bool ListCheck(List * list);
/**
     /brief dump list to dot file and open it 

     /param[in]  list list to dump
     /param[in]  image_file file for dot
     /param[in]  file_image_out file for image

     /return void
*/
void ListDump(List * list, const char * file_image_out, const char * image_file);

void ListDumpNode(FILE * file, Item * item , size_t number,const char * color);
