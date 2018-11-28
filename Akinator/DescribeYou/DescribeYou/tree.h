#pragma once

#include "pch.h"

typedef size_t data_t;

#define BUFF_FOR_DOT_CALL 200
#define BUFF_COLOR_SIZE 100

struct Node {
    Node * parent = nullptr;
    Node * right = nullptr;
    Node * left = nullptr;
    data_t data = nullptr;
};

Node * TreeNodeCtor(data_t data);

bool TreeAddLeft(Node * node_parent, Node * node_left);
bool TreeAddRight(Node * node_parent, Node * node_right);

void TreeRemoveNode(Node * node);

bool TreeOk(Node * node);

void TreeDumpDot(Node * node, const char * dot_file, const char * png_file, bool show = 0);

/// do not use this functions in your code 
void NodeFreeRecur(Node * node);
void NodeFree(Node * node);

bool NodePrintToDot(Node * node, FILE * file);
