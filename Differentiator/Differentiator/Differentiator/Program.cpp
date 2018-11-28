#include "pch.h"

using namespace winrt;

// This example code shows how you could implement the required main function
// for a Console UWP Application. You can replace all the code inside main
// with your own custom code.

// You should also change the Alias value in the AppExecutionAlias Extension
// in the package.appxmanifest to a value that you define. To edit this file
// manually, open it with the XML Editor.

#define INPUT_FILE "../../../../data/input.txt"
#define OUTPUT_FILE "../../../../data/output.txt"

#define PNG_FILE "../../../data/picture.png"
#define FILE_DOT "../../../data/test.txt"

int main()
{
    /*ReadFormulaFromFile(formula, INPUT_FILE);

    D(formula);

    SaveFormulaToFile(formula, OUTPUT_FILE);*/

    Node * node = (Node*)calloc(1, sizeof(Node));
    Node * node1 = (Node*)calloc(1, sizeof(Node));
    Node * node2 = (Node*)calloc(1, sizeof(Node));
    Node * node3 = (Node*)calloc(1, sizeof(Node));
    Node * node4 = (Node*)calloc(1, sizeof(Node));
    Node * node5 = (Node*)calloc(1, sizeof(Node));
    Node * node6 = (Node*)calloc(1, sizeof(Node));


    TreeAddLeft(node, node1);
    TreeAddRight(node, node2);
    TreeAddLeft(node1, node3);
    TreeAddRight(node1, node4);
    TreeAddLeft(node2, node5);
    TreeAddRight(node2, node6);

    TreeDumpDot(node, FILE_DOT, PNG_FILE, 1);

    Node * node_new = NodeCopy(node);

    TreeDumpDot(node_new, FILE_DOT, PNG_FILE, 1);

    FILE * file;
    errno_t file_state = fopen_s(&file, INPUT_FILE, "w");
    if (file_state) {
        LOG_ERR("can't open file for dot for write", INPUT_FILE);
    }

    FILE * file2;
    errno_t file_state2 = fopen_s(&file2, FILE_DOT, "w");
    if (file_state2) {
        LOG_ERR("can't open file for dot for write", FILE_DOT);
    }

    system("chdir");


    // You can get parsed command-line arguments from the CRT globals.

    //wprintf(L"Parsed command-line arguments:\n");
    //for (int i = 0; i < __argc; i++)
    //{
    //    wprintf(L"__argv[%d] = %S\n", i, __argv[i]);
    //}
    //wprintf(L"Press Enter to continue: лпкдупукпкущоп");
    getchar();
}
