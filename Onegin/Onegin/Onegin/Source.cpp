
#include <iostream>

#include "Sorter.h"

#define FILE_INPUT "../files/input.txt"
#define FILE_OUTPUT_SORTED "../files/output_sorted.txt"
#define FILE_OUTPUT_MIXED "../files/output_mixed.txt"

int main()
{
	Sorter obj(FILE_INPUT);
	obj.SaveSorted(FILE_OUTPUT_SORTED);
	//obj.SaveMixed(FILE_OUTPUT_MIXED);

	system("pause");
}