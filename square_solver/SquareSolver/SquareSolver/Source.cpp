#include <iostream>
#include <cstdlib>
#include "solver.h"

//function to check params
bool check_params(int argc, char** argv);
//function to print equation
bool print_equation(int argc, char** argv, double a, double b, double c);
// get params from args
bool parse_params(int argc, char** argv, double *a, double *b, double *c);


int main(int argc, char** argv)
{
	//checing args 
	if (check_params(argc, argv)) {
		double a = 0, b = 0, c = 0;
		parse_params(argc, argv, &a, &b, &c); // get params from args
		print_equation(argc, argv, a, b, c); // print equation 
		solver equation(a, b, c); // create an equation object
		equation.Calc();
		if (equation.nRoots == UNLIM_ROOTS) {
			std::cout << "every x";
		}
		else if (equation.nRoots == 0) {
			std::cout << "no routs";
		}
		else {
			for (size_t i = 0; i < equation.nRoots; i++)
			{
				std::cout << "rout " << i + 1 << " = " << equation.roots[i] << std::endl;
			}
		}
	}
	return 0;
}

bool check_params(int argc, char** argv)
{
	if (argc != 3 + 1) {
		if (argc == 2) {
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

bool print_equation(int argc, char** argv, double a, double b, double c)
{
	std::cout << a << ((b >= 0) ? "x^2+" : "x^2");
	std::cout << b << ((c >= 0) ? "x+" : "x");
	std::cout << c << std::endl;
	return true;
}

bool parse_params(int argc, char** argv, double *a, double *b, double *c)
{
	*a = std::atof(argv[1]), *b = std::atof(argv[2]), *c = std::atof(argv[3]);
	return true;
}