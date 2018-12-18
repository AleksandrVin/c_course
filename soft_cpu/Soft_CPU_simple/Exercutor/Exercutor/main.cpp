#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "MacrosLib/macros.h"

#include "Exercutor.h"

int main(const int argc, const char ** argv)
{
    assert(argv != nullptr);
    if (argc < 2) {
        LOG_ERR_MESSAGE("provide file");
        return -1;
    }
    if (argc == 2) {
        Process* now = CreateProcessDin(1, argv[1]);
        if (now == nullptr) {
            LOG_ERR_MESSAGE("error in creating process");
        }
        size_t exercuted = RunProces(now);
        DestructProcess(now);
        printf("\nin process id : %d was exercuted %zu commands\n", 1, exercuted);
    }
    puts("\npress enter to exit");
    getc(stdin);
    return 0;
}
