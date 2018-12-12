/**
 /autrhor Aleksandr Vinogradov
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "../../../../Libs/FileReaderLib/ReaderLib.h"
#include "../../../../Libs/TreeLib/tree.h"

#define FILE_WITH_TREE "../../data/tree.txt"
#define FILE_WITH_STRINGS "../../data/strings.txt"

#define FILE_DOT "../../data/dot.dot"
#define PNG_FILE "../../data/png.png"

#define BUFF_STRING_SIZE 100

void StartSearch(Node * tree);
void Sorry();
char * EnterNewName();
bool AskQuestion(char * string);
void Grats();
char * GetQuestion(Node * node , char * new_name);

int main()
{
    //reading strings
    char * buff = nullptr;
    size_t size_of_file = ReadFromFile(FILE_WITH_STRINGS, &buff);
    char ** strings = nullptr;
    size_t amount_of_strings = ParseStringToStrings(buff, &strings);
    free(buff);

    //reading tree
    Node * tree = nullptr;
    size_t amount_of_nodes = ReadTreeFromFileWithStringsNumbers(&tree, strings, amount_of_strings, FILE_WITH_TREE);

    TreeDumpDot(tree, FILE_DOT, PNG_FILE);

    while (true) {
        puts("\"find\" to find name of thing, \"stop\" to exit");
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
        else {
            puts(" can't resolve command");
        }
    }

    FreeStrings(strings, amount_of_strings);
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

/// save tree !!!!