#include <iostream>
#include <cstdlib>
#include "solver.h"

int main(int argc, char** argv)
{
	/*for (int i = 1; i < argc; i++)
	{
		for (int n = 0; n < (sizeof(argv[i]) - 1); n++)
		{
			std::cout << argv[i][n] << ' ';
			//if ((argv[i][n] < '0' || argv[i][n] > '9') && argv[i][n] != '-'  && argv[i][n] != '.') {
			//std::cout << "bad args";
			//return 0;
			//}
		}
	}*/
	if (argc != 3 + 1) {
		std::cout << "bad args";
		return 0;
	}
	else {
		double a = std::atof(argv[1]), b = std::atof(argv[2]), c = std::atof(argv[3]);
		std::cout << "solving for f(x) = ";
		std::cout << a << ((b >= 0) ? "x^2+" : "x^2");
		std::cout << b << ((c >= 0) ? "x+" : "x");
		std::cout << c << std::endl;
		double x1 = 0, x2 = 0;
		solver equation(a, b, c);
		equation.Calc();
		if (equation.nRoots == unlim_roots) {
			std::cout << "every x";
		}
		else {
			for (size_t i = 0; i < equation.nRoots; i++)
			{
				std::cout << "rout " << i + 1 << " = " << equation.roots[i] << std::endl;
			}
			if (equation.nRoots == 0) {
				std::cout << "no routs";
			}
		}
	}
	return 0;
}