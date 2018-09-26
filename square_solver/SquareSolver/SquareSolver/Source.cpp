#include <iostream>
#include <cstdlib>
#include "solver.h"

#define ROOTS_AMOUNT 3
/**
 /brief func to check input params

 /param[in] argc 
 /param[in] argv

 /return bool true is args true
*/
bool check_params(int argc, char** argv);
/**
 /brief to print equation

 /param[in]  a a-coeficient
 /param[in]  b b-coeficient
 /param[in]  c c-coeficient

 /return bool true is printed
*/
void print_equation(double a, double b, double c);
/**
 /brief get params from args

 /param[in] argc amount of args
 /param[in] argv arguments verctor of string
 /param[in] a a-coeficient
 /param[in] b b-coeficient
 /param[in] c c-coeficient

 /return int amount of readed params
*/
int parse_params(int argc, char** argv, const double *a, const double *b, const double *c);


int main(int argc, char** argv)
{
	double a = 0, b = 0, c = 0;
	if (parse_params(argc, argv, &a, &b, &c) == ROOTS_AMOUNT){
		print_equation(a, b, c);
		solver equation(a, b, c); 
		equation.Calc();
		equation.Print_roots();
	}
	else {
		std::cout << "incorrect input";
	}
	return 0;
}

bool check_params(int argc, char** argv)
{
	if (argc != ROOTS_AMOUNT + 1) {
		if (argc == 1 + 1) {
			if (argv[1][0] == 'h') {
				std::cout << "provide 3 args: a , b , c of square equation";
			}
			else {
				std::cout << "bad args";
			}
		}
		else {
			std::cout << "bad args";
		}
		return false;
	}
	else {
		return true;
	}
}

void print_equation(double a, double b, double c)
{
	std::cout << a << ((b >= 0) ? "x^2+" : "x^2");
	std::cout << b << ((c >= 0) ? "x+" : "x");
	std::cout << c << std::endl;
}

int parse_params(int argc, char** argv, const double *a, const double *b, const double *c)
{
	if (check_params(argc, argv)){
		return sscanf_s(argv[1], "%lg", a) + sscanf_s(argv[2], "%lg", b) + sscanf_s(argv[3], "%lg", c);
	}
	else{
		return 0;
	}
}