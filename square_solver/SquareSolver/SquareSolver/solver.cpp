#include "solver.h"

void solver::Calc()
{
	calculated = true;
	if (arguments[0] == 0) {
		if (arguments[1] == 0) {
			if (arguments[2] == 0) { // every root 
				nRoots = UNLIM_ROOTS;
			}
			else { // no roots // if c_arg != 0 //
				nRoots = 0;
			}
		}
		else { // only one root 
			nRoots = 1;
			roots[0] = -arguments[2] / arguments[1];
		}
	}
	else { // calculate using discriminant 
		double discr = arguments[1] * arguments[1] - 4 * arguments[0]*arguments[2];
		if (discr > 0)
		{
			discr = std::sqrt(discr);
			roots[0] = (-arguments[1] + discr) / 2 / arguments[0];
			roots[1] = (-arguments[1] - discr) / 2 / arguments[0];
			nRoots = 2;
		}
		else if (discr == 0)
		{
			roots[0] = (-arguments[1]) / 2 / arguments[0];
			nRoots = 1;
		}
		else {
			nRoots = 0;
		}
	}
}

solver::solver(double a, double  b, double c)
{
	assert(std::isfinite(a));
	assert(std::isfinite(b));
	assert(std::isfinite(c));
	arguments[0] = a;
	arguments[1] = b;
	arguments[2] = c;
	std::cout << "this is solver" << arguments[0] << ' ' << arguments[1] << ' ' << arguments[2] << std::endl;
}


solver::~solver()
{
}
