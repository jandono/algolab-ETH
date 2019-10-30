#include <iostream>
#include <cassert>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

// -32y + 64
// x + y	≤	7
// -x + 2y	≤	4
// x	≥	0
// y	≥	0
// y	≤	4

// choose exact integral type
typedef CGAL::Gmpz ET;

// program and solution types
typedef CGAL::Quadratic_program<double> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

int main(){
	// by default, we have a nonnegative LP with Ax <= b
	Program lp(CGAL::SMALLER, true, 0, false, 0); 

	const int X = 0;
	const int Y = 1;
	lp.set_a(X, 0, 1); 	lp.set_a(Y, 0, 1);	lp.set_b(0, 7);
	lp.set_a(X, 1, -1);	lp.set_a(Y, 1, 2);	lp.set_b(1, 4);
	lp.set_a(X, 2, -1); lp.set_a(Y, 2, 0); 	lp.set_b(2, 0);
	lp.set_u(Y, true, 4);
	lp.set_c(X, 0);
	lp.set_c(Y, -32);
	lp.set_c0(64);

	// solve the program, using ET as the exact type
	Solution s = CGAL::solve_linear_program(lp, ET());
  	assert (s.solves_linear_program(lp));

	// output solution
	std::cout << s; 

	return 0;
}