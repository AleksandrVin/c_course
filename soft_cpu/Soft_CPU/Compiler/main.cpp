/**
 /file
 /brief main console application of Compiler

 /author Vinogradov Aleksandr
*/

#include <stdio.h>
#include <assert.h>

#include "Compiler.h"

// files to compile
#define FILE_TO_COMPILE "prog.softasm"
// files for prepocessor
#define FILE_FOR_PREPROCESSOR "preproc.softasm"
// files for output of Compiler 
#define FILE_OUT_BIN "../Executor/RUN.softexe"

int main()
{
	Compiler* progect = CompilerCtorDin();
	assert(progect != nullptr);

	size_t size_of_preproc_file = CompilerPreprocessor(progect, FILE_TO_COMPILE, FILE_FOR_PREPROCESSOR);;
	assert(size_of_preproc_file > 0);

	//size_t size_of_bin_file = CompilerCompile(progect, FILE_FOR_PREPROCESSOR, FILE_OUT_BIN);

    CompilerDtorDin(progect);

	system("pause");
}
