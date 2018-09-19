#include "solver.h"

void solver::Calc()
{
	calculated = true;
	if (a_arg == 0) {
		if (b_arg == 0) {
			if (c_arg == 0) { // every root 
				nRoots = unlim_roots;
			}
			else { // no roots // if c_arg != 0 //
				nRoots = 0;
			}
		}
		else { // only one root 
			nRoots = 1;
			roots[0] = -c_arg / b_arg;
		}
	}
	else { // calculate using discriminant 
		double discr = b_arg * b_arg - 4 * a_arg*c_arg;
		discr = std::sqrt(discr);
		if (discr > 0)
		{
			roots[0] = (-b_arg + discr) / 2 / a_arg;
			roots[1] = (-b_arg - discr) / 2 / a_arg;
			nRoots = 2;
		}
		else if (discr == 0)
		{
			roots[0] = (-b_arg) / 2 / a_arg;
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
	assert(std::isfinite(a));
	assert(std::isfinite(a));
	a_arg = a;
	b_arg = b;
	c_arg = c;
}


solver::~solver()
{
}
