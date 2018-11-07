#include <stdio.h>

#include "Exercutor.h"

#define FILE_INPUT "RUN.softexe"

int main(int argc, char **argv)
{
    //if (argc == 1) {
    //    LOG_ERR("no file to run/", "provide file to run");
    //}

    //for (size_t i = 1; i < size_t(argc); i++) {
    //    Process* now = CreateProcessDin(i , argv[i]);
    //    size_t exercuted = RunProces(now);
    //    DestructProcess(now);
    //    printf("\nin process id : %d was exercuted %d commands", i, exercuted);
    //}

        Process* now = CreateProcessDin(1, FILE_INPUT);
        size_t exercuted = RunProces(now);
        DestructProcess(now);
        printf("\nin process id : %d was exercuted %d commands", 1, exercuted);
	//Stack *ex = nullptr;

	//ex = StackCtorDin();
	//StackPush(ex, 4235775);
	//printf("%d", StackPop(ex));
	//StackDtorDin(ex);

}