// RecursivSliding.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

#define FILE_INPUT "formula.txt"

#define MAX_INPUT_LENGTH 200

int main()
{
    //puts("we will print equation now : ");

    //char * input_string = nullptr;
    //size_t string_size = 0;
    //string_size = ReadFromFile(FILE_INPUT, &input_string);
    //PrintString(input_string);
    puts("This is simple calculator for equation like this ## 1 - 10 + ( 51  + sin(50.0045563 - 1))* 6 ## \n");

    puts("use only this operations\n");
    puts("\tsin(number)\n");
    puts("\tcos(number)\n");
    puts("\t+\n");
    puts("\t-\n");
    puts("\t*\n");
    puts("\t/\n");
    puts("\t(equation)\n");
    puts("\tuse also spaces\n");

    puts("enter equation\n");

    char input_string[MAX_INPUT_LENGTH];
    gets_s(input_string, MAX_INPUT_LENGTH);

    double result = ParseAndSolveEquation(input_string);

    puts("\nresult is\n");

    printf("\t%f\n", result);

    puts("\ntap something to exit");
    getchar();
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
