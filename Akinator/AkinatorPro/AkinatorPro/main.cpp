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

    TreeDumpDot(tree, FILE_DOT, PNG_FILE, 1);

    while (true) {
        puts("\n\"find\" to find name of thing, \"stop\" to exit\n");
        char mode[BUFF_STRING_SIZE] = "";
        gets_s(mode, BUFF_STRING_SIZE);
        if (strcmp(mode, "find") == 0) {
            //FindAnswer();
            puts("ogoihergolgjg");
        }
        else if (strcmp(mode, "stop") == 0)
        {
            break;
        }
        else {
            puts("\n can't resolve command");
        }
    }
    return 0;
}