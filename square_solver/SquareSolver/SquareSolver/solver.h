//---------------------------------------------------
//! class to solve square equation 
//!
//! 
//! 
//!  
//! @note create class with arg of equation then use Calc method 
//---------------------------------------------------
#ifndef SOLVER
#define SOLVER

#include <cmath>
#include <cassert>
#include <iostream>

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
	double arguments[];
};

#endif
