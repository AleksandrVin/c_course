#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "MacrosLib/macros.h"

#include "Compiler.h"

int main(const int argc, const char ** argv)
{
    assert(argv != nullptr);
    if (argc < 2) {
        LOG_ERR_MESSAGE("provide file");
        return -1;
    }
    if (argc < 4) {
        LOG_ERR_MESSAGE("provide right call with 2 args");
        return -1;
    }
    if (argc == 4) {
        if (strcmp(argv[2], "-o") == 0) {
            const bool result_preproc = Preprocess(argv[1], argv[3]);
            if (!result_preproc) {
                LOG_ERR_MESSAGE("error in preprocessing");
            }
            //const bool result = Compiler(argv[3], argv[3]);
            //if (!result) {
            //    LOG_ERR_MESSAGE("error in compiling");
            //    return -1;
            //}
        }
        else {
            LOG_ERR_MESSAGE("bad args");
            return -1;
        }
    }
    return 0;
}