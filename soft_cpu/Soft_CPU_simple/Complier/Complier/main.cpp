#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "MacrosLib/macros.h"
#include "ListLib/listChar.h"

#include "Compiler.h"
#include "Preprocessor.h"

int main(const int argc, const char ** argv)
{
    assert(argv != nullptr);
    if (argc < 2) {
        LOG_ERR_MESSAGE("provide file");
        return -1;
    }
    if (argc < 6) {
        LOG_ERR_MESSAGE("provide right call with 2 args");
        return -1;
    }
    if (argc == 6) {
        if (strcmp(argv[2], "-o") == 0 && strcmp(argv[4], "-p") == 0) {
            const bool result_preproc = Preprocess(argv[1], argv[5]);
            if (!result_preproc) {
                LOG_ERR_MESSAGE("error in preprocessing");
            }
            Label labels[MAX_AMOUNT_OF_LABELS];
            size_t labels_amount = 0;
            bool result = Compiler(argv[5], argv[3], labels, false , &labels_amount);
            result = Compiler(argv[5], argv[3], labels, true , &labels_amount);
            if (!result) {
                LOG_ERR_MESSAGE("error in compiling");
                return -1;
            }
        }
        else {
            LOG_ERR_MESSAGE("bad args");
            return -1;
        }
    }
    puts("\npress enter to exit");
    getc(stdin);
    return 0;
}