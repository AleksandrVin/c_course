// DescribeYou.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

#define PNG_FILE "../../Dot/picture.png"
#define FILE_DOT "../../Dot/test.txt"

#define FILE_WITH_TREE "../../data/tree.txt"
#define FILE_WITH_STRINGS "../../data/strings.txt"

#define BUFF_STRING_SIZE 100

int main()
{
    setlocale(LC_CTYPE, "rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    //loaing data from disk
    char ** strings = nullptr;
    size_t strings_amount = LoadStrings(FILE_WITH_STRINGS , &strings);

    PrintStrings(strings_amount, strings);
    //Node * tree = LoadTreeFromFile(FILE_WITH_TREE,strings_amount);

    while (true) {
        puts("\n\"find\" to find name of thing, \"stop\" to exit\n");
        char mode[BUFF_STRING_SIZE] = "";
        gets_s(mode, BUFF_STRING_SIZE);
        if (strcmp(mode,"find") == 0) {
            //FindAnswer();
            puts("ogoihergolgjg");
        }
        else if (strcmp(mode,"stop") == 0)
        {
            break;
        }
        else {
            puts("\n can't resolve command");
        }
    }

    ////char * string = (char*)calloc(100, sizeof(char));
    ////gets_s(string, 100);
    ////puts(string);

    //char data1[100]  = "node_L";
    //char data2[100] = "node_R";
    //char data[100] = "head";
    //Node * Tree = TreeNodeCtor(data);
    //Node * node_arr1[10];
    //Node * node_arr2[10];
    //Node * node_arr3[10];
    //for (size_t i = 0; i < 10; i++)
    //{
    //    node_arr1[i] = TreeNodeCtor(data1);
    //    node_arr3[i] = TreeNodeCtor(data1);
    //    if (i > 0) {
    //        TreeAddLeft(node_arr1[i - 1], node_arr1[i]);
    //        TreeAddRight(node_arr1[i - 1], node_arr3[i]);
    //    }
    //    else {
    //        TreeAddLeft(Tree, node_arr1[0]);
    //    }
    //}
    //for (size_t i = 0; i < 10; i++)
    //{
    //    node_arr2[i] = TreeNodeCtor(data2);
    //    if (i > 0) {
    //        TreeAddRight(node_arr2[i - 1], node_arr2[i]);
    //    }
    //    else {
    //        TreeAddRight(Tree, node_arr2[0]);
    //    }
    //}
    ////TreeRemoveNode(Tree->right);
    //TreeDumpDot(Tree, FILE_DOT, PNG_FILE, 0);
    return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
