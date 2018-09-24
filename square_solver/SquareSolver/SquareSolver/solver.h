/**
 \brief class to solve square equation 
 \param[out] nRouts , routs[2] number of roots and array of routs 
 \param[out] calculated True, when equation calculated 
 
 
  
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
	double roots[2]; // 
	solver(double a, double b, double c); // create class and gets params of equation 
	~solver();
private:
	double arguments[ARGS_AMOUNT];
};

#endif
