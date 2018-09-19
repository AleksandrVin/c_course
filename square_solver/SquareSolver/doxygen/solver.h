//---------------------------------------------------
//! class to solve square equation 
//!
//! 
//! 
//!  
//! @note create class with arg of equation then use Calc method 
//---------------------------------------------------
#pragma once

#include <cmath>
#include <cassert>

#ifndef unlim_roots
#define unlim_roots -1
class solver
{
public:
	void Calc();  // calculate equation 
	bool calculated = false; // if equation calculated true,else false 
	int nRoots = 0;
	double roots[2]; // 
	solver(double a, double b, double c); // create class and gets params of equation 
	~solver();
private:
	double a_arg = 0, b_arg = 0, c_arg = 0;
};

#endif