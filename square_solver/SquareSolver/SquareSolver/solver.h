/**
 \brief class to solve square equation

 @note create class with arg of equation then use Calc method
*/
#ifndef SOLVER
#define SOLVER

#include <cmath>
#include <cassert>
#include <iostream>

#define ARGS_AMOUNT 3
#define UNLIM_ROOTS -1
class solver
{
public:
	void Calc();  // calculate equation
	bool calculated = false; // if equation calculated true,else false 
	size_t nRoots = 0;
	double roots[2];
	/**
	 /brief prints roots of equation
	*/
	void Print_roots();
	/**
     /brief construct class with args

     /param[in]  a a-coeficient
	 /param[in]  b b-coeficient
	 /param[in]  c c-coeficient
    */
	solver(double a, double b, double c); // create class and gets params of equation 
	~solver();
private:
	/**
     /brief construct class with args

     /param[in]  a a-coeficient
     /param[in]  b b-coeficient

	 /return double answer
    */
	double Solve_line_equation(double a, double b);
	double arguments[ARGS_AMOUNT];
};

#endif
