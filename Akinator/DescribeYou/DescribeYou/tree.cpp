#include "pch.h"
#include "tree.h"

Node * TreeNodeCtor(data_t data)
{
    Node * node = (Node*)calloc(1, sizeof(Node));
    if (node == nullptr) {
        return nullptr;
    }
    node->data = nullptr;
    node->left = nullptr;
    node->right = nullptr;
    node->parent = nullptr;
    node->data = data;
    return node;
}

bool TreeAddLeft(Node * node_parent, Node * node_left)
{
    assert(node_parent != nullptr);
    assert(node_left != nullptr);

    if (node_parent->left != nullptr) {
        LOG_ERR_MESSAGE("node parent already have left child");
        return false;
    }
    if (node_left->parent != nullptr) {
        LOG_ERR_MESSAGE("left child already have parent");
        return false;
    }
    node_parent->left = node_left;
    node_left->parent = node_parent;
    return true;
}

bool TreeAddRight(Node * node_parent, Node * node_right)
{
    assert(node_parent != nullptr);
    assert(node_right != nullptr);

    if (node_parent->right != nullptr) {
        LOG_ERR_MESSAGE("node parent already have right child");
        return false;
    }
    if (node_right->parent != nullptr) {
        LOG_ERR_MESSAGE("right child already have parent");
        return false;
    }
    node_parent->right = node_right;
    node_right->parent = node_parent;
    return true;
}

void TreeRemoveNode(Node * node)
{
    assert(node != nullptr);

    if (node->parent == nullptr) {
    }
    else {
        if (node->parent->left == node) {
            node->parent->left = nullptr;
        }
        else {
            node->parent->right = nullptr;
        }
    }
    NodeFreeRecur(node);
}

bool TreeOk(Node * node)
{
    assert(node != nullptr);

    if (node->data == nullptr) {
        LOG_ERR_MESSAGE("no data in node");
        return false;
    }
    if (node->left != nullptr) {
        if (!TreeOk(node->left)) {
            LOG_ERR_MESSAGE("broken left node");
            return false;
        }
    }
    if (node->right != nullptr) {
        if (!TreeOk(node->right)) {
            LOG_ERR_MESSAGE("broken right node");
            return false;
        }
    }
    return true;
}

void TreeDumpDot(Node * node, const char * dot_file, const char * png_file, bool show)
{
    FILE * file;
    errno_t file_state = fopen_s(&file, dot_file, "w");
    if (file_state) {
        LOG_ERR("can't open file for dot for write", dot_file);
    }
    else {
        fprintf_s(file, "digraph {\n");

        fprintf_s(file, "node[shape = record, height = .1 , style=filled];\n");
        NodePrintToDot(node, file);
        fprintf_s(file, "}");

        fclose(file);


        char dot_call[BUFF_FOR_DOT_CALL] = "";
        if (show) {
            char dot_call[BUFF_FOR_DOT_CALL] = "dotty";
            strcat_s(dot_call, BUFF_FOR_DOT_CALL, " ");
            strcat_s(dot_call, BUFF_FOR_DOT_CALL, dot_file);

            system(dot_call);
        }
        else {
            char dot_call[BUFF_FOR_DOT_CALL] = "dot";
            const char * dot_arg = "-Tpng -o";
            strcat_s(dot_call, BUFF_FOR_DOT_CALL, " ");
            strcat_s(dot_call, BUFF_FOR_DOT_CALL, dot_file);
            strcat_s(dot_call, BUFF_FOR_DOT_CALL, " ");
            strcat_s(dot_call, BUFF_FOR_DOT_CALL, dot_arg);
            strcat_s(dot_call, BUFF_FOR_DOT_CALL, " ");
            strcat_s(dot_call, BUFF_FOR_DOT_CALL, png_file);
            strcat_s(dot_call, BUFF_FOR_DOT_CALL, " ");

            system(dot_call);
        }
    }
}


void NodeFreeRecur(Node * node)
{
    assert(node != nullptr);

    if (node->left != nullptr) {
        NodeFreeRecur(node->left);
    }
    else if (node->right != nullptr) {
        NodeFreeRecur(node->right);
    }
    else {
        NodeFree(node);
    }
}

void NodeFree(Node * node)
{
    assert(node != nullptr);

    free(node);
}

bool NodePrintToDot(Node * node, FILE * file)
{
    if (!node) {
        return 0;
    }

    char color[BUFF_COLOR_SIZE] = "";
    if (TreeOk(node)) {
        strcpy_s(color, BUFF_COLOR_SIZE, "mediumturquoise");
    }
    else {
        strcpy_s(color, BUFF_COLOR_SIZE, "red");
    }

    NodePrintToDot(node->left, file);

    fprintf_s(file, "node");
    fprintf_s(file, "%d", (size_t)(node));
    fprintf_s(file, "[label = \"<f0> left| <f1> ");
    fprintf_s(file, "%s", node->data);
    fprintf_s(file, " | <f2> right| <f3> parent\" , color=");
    fprintf_s(file, "%s", color);
    fprintf_s(file, " ];\n");

    if (node->left != nullptr) {
        fprintf_s(file, "\"node");
        fprintf_s(file, "%d", (size_t)(node));
        fprintf_s(file, "\":f0 -> \"node");
        fprintf_s(file, "%d", (size_t)(node->left));
        fprintf_s(file, "\" : f1;");
    }

    if (node->right != nullptr) {
        fprintf_s(file, "\"node");
        fprintf_s(file, "%d", (size_t)(node));
        fprintf_s(file, "\":f2 -> \"node");
        fprintf_s(file, "%d", (size_t)(node->right));
        fprintf_s(file, "\" : f1;");
    }

    if (node->parent != nullptr) {
        fprintf_s(file, "\"node");
        fprintf_s(file, "%d", (size_t)(node));
        fprintf_s(file, "\":f3 -> \"node");
        fprintf_s(file, "%d", (size_t)(node->parent));
        fprintf_s(file, "\" : f1;");
    }

    NodePrintToDot(node->right, file);

    return true;
}
