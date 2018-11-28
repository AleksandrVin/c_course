#include "List.h"

List * ListCtorDin()
{
    List * new_list = (List*)calloc(1, sizeof(List));
    assert(new_list != nullptr);
    return new_list;
}

void ListDtorDin(List * list)
{
    assert(list != nullptr);

    Item * current = list->tail;
    Item * next;
    while (current != nullptr)
    {
        next = current->next;
        listFreeElem(current);
        current = next;
    }
    free(list);
}

Item * ListInsert(List * list, data_t data)
{
    assert(list != nullptr);

    Item * item = ListCreateItem();
    assert(item != nullptr);

    if (list->head == nullptr) {
        list->head = item;
        list->tail = item;
        list->size = 1;
    }
    else {
        item->prev = list->head;
        list->head->next = item;
        list->head = item;
        list->size++;
    }
    item->data = data;
    return item;
}

bool ListDelete(List * list, data_t data)
{
    assert(list != nullptr);
    Item * item = ListSearch(list, data);
    if (item != nullptr) {
        ListRemove(list, item);
        return true;
    }
    return false;
}

bool ListRemove(List * list, Item * item)
{
    assert(list != nullptr);
    assert(item != nullptr);

    if (item->next == nullptr)
    {
        if (item->prev == nullptr) {
            list->head = nullptr;
            list->head = nullptr;
        }
        else {
            list->head = item->prev;
            item->prev->next = item->next;
        }
    }
    else if (item->prev == nullptr) {
        list->tail = item->next;
        item->next->prev = nullptr;
    }
    else {
        item->prev->next = item->next;
        item->next->prev = item->prev;
    }
    listFreeElem(item);
    list->size--;
    return false;
}

Item * ListSearch(List * list, data_t data)
{
    assert(list != nullptr);
    Item * curr_item = list->tail;
    while (curr_item != nullptr) 
    {
        if (curr_item->data == data) {
            return curr_item;
        }
        curr_item = curr_item->next;
    }
    return nullptr;
}

Item * ListCreateItem()
{
    Item * item = (Item*)calloc(1, sizeof(Item));
    assert(item != nullptr);
    item->next = nullptr;
    item->prev = nullptr;
    item->data = 0;
    return item;
}

void listFreeElem(Item * item)
{
    assert(item != nullptr);
    free(item);
}

bool ListCheck(List * list)
{
    assert(list != nullptr);
    return true;
}

void ListDump(List * list, const char * file_dot_out, const char * image_file)
{
    FILE * file_out;
    errno_t file_state = fopen_s(&file_out, file_dot_out, "w");
    if (file_state) {
        LOG_ERR("can't open file for dot", file_dot_out);
    }
    fprintf_s(file_out, "digraph {\n");

    fprintf_s(file_out, "node[shape = record, height = .1 , style=filled, color=\".7 .3 1.0\"];\n");
    ListDumpNode(file_out, list->tail, 0 , "red");
    fprintf_s(file_out, "}");

    fclose(file_out);

    char dot_call[BUFF_FOR_DOT_CALL] = "dot -Tpng";
    const char * dot_arg = "-o";
    strcat_s(dot_call, BUFF_FOR_DOT_CALL, " ");
    strcat_s(dot_call, BUFF_FOR_DOT_CALL, file_dot_out);
    strcat_s(dot_call, BUFF_FOR_DOT_CALL, " ");
    strcat_s(dot_call, BUFF_FOR_DOT_CALL, dot_arg);
    strcat_s(dot_call, BUFF_FOR_DOT_CALL, " ");
    strcat_s(dot_call, BUFF_FOR_DOT_CALL, image_file);
    strcat_s(dot_call, BUFF_FOR_DOT_CALL, " ");
    //LOG_ERR(dot_call, "this is dot call");
    system(dot_call);
}

void ListDumpNode(FILE * file, Item * item, size_t number, const char * color)
{
    if (item->next != nullptr) {
        if (number == 0) {
            fprintf_s(file, "node");
            fprintf_s(file, "%d", number);
            fprintf_s(file, "[label = \"<f0> prev| <f1> ");
            fprintf_s(file, "%d", item->data);
            fprintf_s(file, " | <f2> next\" , color=");
            fprintf_s(file, "%s", color);
            fprintf_s(file, " ];\n");
        }
        fprintf_s(file, "node");
        fprintf_s(file, "%d", number + 1);
        fprintf_s(file, "[label = \"<f0> prev| <f1> ");
        fprintf_s(file, "%d", item->next->data);
        fprintf_s(file, " | <f2> next\" , color=");
        fprintf_s(file, "%s", color);
        fprintf_s(file, " ];\n");

        fprintf_s(file, "\"node");
        fprintf_s(file, "%d", number);
        fprintf_s(file, "\":f2 -> \"node");
        fprintf_s(file, "%d", number + 1);
        fprintf_s(file, "\" : f1;");

        fprintf_s(file, "\"node");
        fprintf_s(file, "%d", number + 1);
        fprintf_s(file, "\":f0 -> \"node");
        fprintf_s(file, "%d", number);
        fprintf_s(file, "\" : f1;");
        //fprintf_s(file, "    %d -> %d;\n", item->data, item->next->data);
        ListDumpNode(file, item->next, ++number,color);
    }
}
