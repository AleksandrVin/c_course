#pragma once

typedef char* data_t;

struct Node {
    data_t data;
    Node * left = nullptr;
    Node * right = nullptr;
};

struct Tree {
    Node * root;
    size_t size;
};