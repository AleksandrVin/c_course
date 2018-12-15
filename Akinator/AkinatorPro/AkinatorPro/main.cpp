/**
 /autrhor Aleksandr Vinogradov
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "FileReaderLib/ReaderLib.h"
#include "TreeLib/tree.h"

#define FILE_WITH_TREE "../../data/tree.txt"
#define FILE_WITH_STRINGS "../../data/strings.txt"

#define FILE_DOT "../../data/dot1.dot"
#define PNG_FILE "../../data/png.png"

constexpr auto BUFF_STRING_SIZE = 100;

void StartSearch(Node * tree);
void Sorry();
char * EnterNewName();
bool AskQuestion(char * string);
void Grats();
char * GetQuestion(Node * node, char * new_name);

Node * TreeSearch(Node * tree, const char * string);

void DescribeObject(Node * tree);

void DifferenceObject(Node * start1, Node * start2);


int main()
{
    //reading strings
    char * buff = nullptr;
    size_t size_of_file = ReadFromFile(FILE_WITH_STRINGS, &buff);
    char ** strings = nullptr;
    size_t amount_of_strings = ParseStringToStrings(buff, &strings);

    //reading tree
    Node * tree = nullptr;
    size_t amount_of_nodes = ReadTreeFromFileWithStringsNumbers(&tree, strings, amount_of_strings, FILE_WITH_TREE);

    while (true) {
        puts(" \
            \"find\" to find name of thing\n \
            \"show_tree\" to open tab with tree\n \
            \"save_tree\" to save tree picture in file\n \
            \"describe\" to get describtion of object\n \
            \"difference\" to see difference of two objects\n \
            \"stop\" to exit\n");
        char mode[BUFF_STRING_SIZE] = "";
        gets_s(mode, BUFF_STRING_SIZE);
        if (strcmp(mode, "find") == 0) {
            //FindAnswer();
            StartSearch(tree);
            puts("search end");
        }
        else if (strcmp(mode, "stop") == 0)
        {
            break;
        }
        else if (strcmp(mode, "show_tree") == 0) {
            TreeDumpDot(tree, FILE_DOT, PNG_FILE, 1);
        }
        else if (strcmp(mode, "save_tree") == 0) {
            TreeDumpDot(tree, FILE_DOT, PNG_FILE);
        }
        else if (strcmp(mode, "describe") == 0) {
            puts("Who you want to describe ?");
            gets_s(mode, BUFF_STRING_SIZE);
            Node * start = TreeSearch(tree, mode);
            if (start != nullptr) {
                DescribeObject(start);
            }
            else {
                puts("can't find");
            }
        }
        else if (strcmp(mode, "difference") == 0) {
            puts("between who?");
            gets_s(mode, BUFF_STRING_SIZE);
            Node * start1 = TreeSearch(tree, mode);
            puts("and who?");
            gets_s(mode, BUFF_STRING_SIZE);
            Node * start2 = TreeSearch(tree, mode);
            if (start1 != nullptr && start2 != nullptr) {
                DifferenceObject(start1, start2);
            }
            else {
                puts("can't find");
            }
        }
        else {
            puts(" can't resolve command");
        }
    }

    SaveTreeToFile(tree, FILE_WITH_TREE, FILE_WITH_STRINGS);

    free(buff);
    NodeFreeRecur(tree);

    return 0;
}

void StartSearch(Node * tree)
{
    if (AskQuestion(tree->data)) {
        if (tree->right == nullptr) {
            Grats();
        }
        else {
            StartSearch(tree->right);
        }
    }
    else {
        if (tree->left == nullptr) {
            Sorry();
            char * new_string = EnterNewName();
            char * new_question = GetQuestion(tree, new_string);
            Node * new_node_yes = TreeNodeCtor(new_string);
            Node * new_node_no = TreeNodeCtor(tree->data);
            tree->data = new_question;
            new_node_yes->parent = tree;
            new_node_no->parent = tree;
            tree->left = new_node_no;
            tree->right = new_node_yes;
        }
        else {
            StartSearch(tree->left);
        }
    }
}

void Sorry()
{
    puts("sorry, we can't find");
}

char * EnterNewName()
{
    printf("Enter name of object : ");
    char * buff = (char*)calloc(BUFF_STRING_SIZE, sizeof(char));
    gets_s(buff, BUFF_STRING_SIZE);
    return buff;
}

bool AskQuestion(char * string)
{
    printf("%s ? Yes or No : ", string);
    char buff[BUFF_STRING_SIZE] = "";
    gets_s(buff, BUFF_STRING_SIZE);
    if (strcmp(buff, "Yes") == 0) {
        return true;
    }
    return false;
}

void Grats()
{
    puts("Yes, I make it!");
}

char * GetQuestion(Node * node, char * new_name)
{
    printf("What difference between %s and %s : ", new_name, node->data);
    char * buff = (char*)calloc(BUFF_STRING_SIZE, sizeof(char));
    gets_s(buff, BUFF_STRING_SIZE);
    return buff;
}

Node * TreeSearch(Node * tree, const char * string)
{
    assert(tree != nullptr);
    if (strcmp(string, tree->data) == 0) {
        return tree;
    }
    if (tree->left != nullptr) {
        Node * result = TreeSearch(tree->left, string);
        if (result != nullptr) {
            return result;
        }
    }
    if (tree->right != nullptr) {
        Node * result = TreeSearch(tree->right, string);
        if (result != nullptr) {
            return result;
        }
    }
    return nullptr;
}

void DescribeObject(Node * tree)
{
    assert(tree != nullptr);

    if (tree->parent != nullptr) {
        printf("this object is is %s\n", tree->data);
        DescribeObject(tree->parent);
    }
}

void DifferenceObject(Node * start1, Node * start2)
{
    assert(start1 != nullptr);
    assert(start2 != nullptr);

    if (start1->parent != nullptr) {
        if (start2->parent != nullptr) {
            Node * copy_1 = start1->parent;
            Node * copy_2 = start2->parent;
            while ((copy_1->parent != copy_2->parent) && copy_1->parent != nullptr && copy_2->parent != nullptr)
            {
                copy_1 = copy_1->parent;
            }
            if (copy_1->parent == copy_2->parent) {
                printf("%s is %s then %s\n", start1->data, copy_1->data, start2->data);
                while (copy_1 != nullptr) {
                    printf("%s and %s same in %s\n", start1->data, start2->data, copy_1->data);
                    copy_1 = copy_1->parent;
                }
                return;
            }
            else {
                while ((copy_1->parent != copy_2->parent) && copy_1->parent != nullptr && copy_2->parent != nullptr)
                {
                    copy_2 = copy_2->parent;
                }
                if (copy_1->parent == copy_2->parent) {
                    printf("%s is %s then %s\n", start1->data, copy_1->data, start2->data);
                    while (copy_1 != nullptr) {
                        printf("%s and %s same in %s\n", start1->data, start2->data, copy_1->data);
                        copy_1 = copy_1->parent;
                    }
                    return;
                }
            }
        }
        else {
            puts("Error, is object is defference");
        }
    }
    else {
        puts("Error, is object is defference");
    }
    if (start1->parent != nullptr) {
        if (start2->parent != nullptr) {
            Node * copy_1 = start1->parent;
            Node * copy_2 = start2->parent;
            while ((copy_1->parent != copy_2->parent) && copy_1->parent != nullptr && copy_2->parent != nullptr)
            {
                copy_2 = copy_2->parent;
            }
            if (copy_1->parent == copy_2->parent) {
                printf("%s is %s then %s\n", start1->data, copy_2->data, start2->data);
                while (copy_2 != nullptr) {
                    printf("%s and %s same in %s\n", start1->data, start2->data, copy_2->data);
                    copy_1 = copy_2->parent;
                }
                return;
            }
            else{
                while ((copy_1->parent != copy_2->parent) && copy_1->parent != nullptr && copy_2->parent != nullptr)
                {
                    copy_1 = copy_1->parent;
                }
                if (copy_1->parent == copy_2->parent) {
                    printf("%s is %s then %s\n", start1->data, copy_2->data, start2->data);
                    while (copy_2 != nullptr) {
                        printf("%s and %s same in %s\n", start1->data, start2->data, copy_2->data);
                        copy_1 = copy_2->parent;
                    }
                    return;
                }
            }
        }
        else {
            puts("Error, is object is defference");
        }
    }
    else {
        puts("Error, is object is defference");
    }
}

/// save tree !!!!