#include "Sorter.h"



/*Sorter::Sorter(const char* file_input)
{
	file = std::fopen(file_input,"r");
	assert(file);

	std::fseek(file, 0, SEEK_END); // seek to end
	std::size_t filesize = std::ftell(file); // gets end position
	std::fseek(file, 0, SEEK_SET); // seek to start

	buff = new char[filesize];//create vector of widechar
	std::fread(buff->data(), sizeof(char), buff->size(), file); // read to buff
	std::fclose(file);
	std::cout << "readed " << filesize << std::endl;
}*/


Sorter::Sorter(const char * file_input)
{
	nStrings = readFromFile(file_input);
	printf("readed %d strings\n", nStrings);
	printStrings(nStrings, strings);
	File_readed = true;
}

Sorter::~Sorter()
{
	for (int i = 0; i < nStrings; i++)
	{
		free(strings[i]);
	}
	free(strings);
	free(strings_sorted);
}

bool Sorter::SaveSorted(const char * file_output)
{
	copy_strings_to_strings_sorted(nStrings);
	//std::qsort(strings_sorted, nStrings, sizeof(strings_sorted[0]),reverseCompare);
	printStrings(nStrings, strings_sorted);
	return true;
}

bool Sorter::SaveMixed(const char * file_output)
{
	return false;
}

size_t Sorter::getFileSize(FILE * file_to_seek)
{
	fseek(file_to_seek, 0, SEEK_END); // seek to end 
	size_t file_size = ftell(file_to_seek); // gets end position
	fseek(file_to_seek, 0, SEEK_SET); // seek to start
	return file_size;
}

int Sorter::parseToSrings(const char* buff, size_t size_of_buff)
{
	int string_counter = countStrings(buff, size_of_buff);
	strings = (char**)calloc(string_counter, sizeof(char*));
	int current_string_starts = 0;
	int current_string_lenght = 0;
	int current_string = 0;
	for (size_t i = 0; i < size_of_buff; i++)
	{
		if (buff[i] == '\n' && current_string_lenght) {
			strings[current_string] = (char*)calloc(current_string_lenght, sizeof(char));
			stringCopy(strings[current_string], buff, current_string_starts, current_string_lenght, 0);
			current_string++;
			++current_string_starts += current_string_lenght; 
			current_string_lenght = 0;
		}
		else if(buff[i] != '\n'){
			current_string_lenght++;
		}
	}
	return current_string;
}

int Sorter::readFromFile(const char * file_input)
{
	assert(!fopen_s(&file, file_input, "r")); // assert if file wasn't opened 
	// if file was opened
	printf("file %s opened\n", file_input);
	// get file size and prepare buffer
	size_t file_size = getFileSize(file);
	char_buff = (char*)calloc(file_size, sizeof(char));
	// reading from file to buff
	size_t readed_size = 0;
	readed_size = fread(char_buff, sizeof(char), file_size, file);
	assert(readed_size);
	// close the file
	fclose(file);
	int strings_amount = parseToSrings(char_buff, readed_size);
	free(char_buff);
	printf("file %s was readed\n", file_input);
	return strings_amount;
}

int Sorter::countStrings(const char * buff, size_t size_of_buff)
{
	int string_counter = 0;
	bool last_was_free = true;
	for (size_t i = 0; i < size_of_buff; i++)
	{
		if (buff[i] == '\n' && !last_was_free) {
			last_was_free = true;
			string_counter++;
		}
		else if(buff[i] != '\n'){
			last_was_free = false;
		}
	}
	return string_counter;
}

const char* Sorter::stringCopy(char* str_to, const char* str_from, int begin_from, int lenght, int begin_to) {
	lenght += begin_from - 1;
	for (begin_from; begin_from < lenght; begin_from++)
	{
		str_to[begin_to++] = str_from[begin_from];
	}
	str_to[begin_to] = '\0';
	return str_from;
}

int Sorter::reverseCompare(const void* a, const void* b)
{
	const char* arg1 = *(const char**)a;
	const char* arg2 = *(const char**)b;

	int len1 = findSizeOfString(arg1);
	int len2 = findSizeOfString(arg2);

	if (len1 >= len2) {
		for (int i = len1 - 1; i >= 0; i--)
		{
			if (arg1[i] == arg2[i]) {
				continue;
			}
			else if(arg1[i] > arg2[i]){
				return 1;
			}
			else {
				return -1;
			}
		}
	}
	else {
		for (int i = len2 - 1; i >= 0; i--)
		{
			if (arg1[i] == arg2[i]) {
				continue;
			}
			else if (arg1[i] > arg2[i]) {
				return 1;
			}
			else {
				return 1;
			}
		}
	}
	return 0;
}

void Sorter::copy_strings_to_strings_sorted(int nStrings)
{
	strings_sorted = (char**)calloc(nStrings, sizeof(char*));
	for (int i = 0; i < nStrings; i++)
	{
		strings_sorted[i] = strings[i];
	}
}

int Sorter::cmp(const void * a, const void * b)
{
	return strcmp(*(char**)a,*(char**)b);
}


int Sorter::printStrings(int strings_amount , char** strings)
{
	for (int i = 0; i < strings_amount; i++)
	{
		printf("%s\n ", strings[i]);
	}
	return strings_amount;
}

int Sorter::findSizeOfString(const char * string)
{
	int size = 0;
	while (*string++ != '\0') {
		size++;
	}
	return size - 1;
}

/*bool Sorter::SaveSorted(const char* file_output)
{
	file = std::fopen(file_output, "w");
	assert(file);
	int b;
	b = std::fwrite(buff->data(), sizeof(char), buff->size(), file);
	std::fclose(file);
	std::cout << "write to file " << b;
	return true;
}*/

/*bool Sorter::SaveMixed(const char* file_output)
{
	parse_to_strings();
	std::sort(strings.begin(), strings.end());
	for (auto now : strings)
	{
		std::cout << now << std::endl;
	}
	return true;
}
bool Sorter::cmp(const char ** a, const char ** b)
{
	return false;
}
/**
 /brief parse buffer to strings

 /return amount of parsed strings
*/
/*int Sorter::parse_to_strings()
{
	int string_amount = 0;
	strings.push_back("");
	bool empty = true;
	for(auto character : *buff)
	{
		if (character != '\n' && character != '\r') {
			strings[string_amount].push_back(character);
			empty = false;
		}
		else if(!empty){
			empty = true;
			string_amount++;
			strings.push_back("");
		}
		else continue;
	}
	return string_amount + 1;
}
*/