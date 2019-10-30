/*
	Our variables are the amount of food we buy from all of the available foods. Hence we have M variables.
	Our constraints are on the nutritients and are defined by min and max value so we split them into 2 for every constraint ending up with 2N constraints.
	
	The constraints look like:
		n_0 * q_0 + n_0 * q_1 + ...... + n_0 * q_m-1 >= min
		n_0 * q_0 + n_0 * q_1 + ...... + n_0 * q_m-1 <= max
		.
		.
		.
		n_n * q_0 + n_n * q_1 + ...... + n_n * q_m-1 >= min
		n_n * q_0 + n_n * q_1 + ...... + n_n * q_m-1 <= max

	The objective function looks like:
		min q_0 * p_0 + q_1 * p_1 + ....... + q_m-1 * p_m-1
*/

#include <iostream>
#include <cassert>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

using namespace std;

// choose exact integral type
typedef CGAL::Gmpz ET;

// program and solution types
typedef CGAL::Quotient<ET> SolT;
typedef CGAL::Quadratic_program<double> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

double floor_to_double(const SolT& x){
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}

int n, m, mini, maxi, p, coef;

void testcase(int n, int m){

	Program lp(CGAL::SMALLER, true, 0, false, 0);

	for(int i=0;i<n;i++){
		cin >> mini >> maxi;
		lp.set_b(i, maxi);
		lp.set_b(n + i, mini);
		lp.set_r(n + i, CGAL::LARGER);
	}

	for(int j=0;j<m;j++){

		cin >> p;
		lp.set_c(j, p);

		for(int i=0;i<n;i++){
			cin >> coef;
			lp.set_a(j, i, coef);
			lp.set_a(j, n + i, coef);
		}
	}

	// solve the program, using ET as the exact type
	Solution s = CGAL::solve_quadratic_program(lp, ET());
  	assert (s.solves_quadratic_program(lp));

	// output solution
  	if(s.is_optimal()){
  		double val = floor_to_double(s.objective_value());
  		cout << val << endl;
  	}else
  	if(s.is_unbounded()){
  		cout << "unbounded" << endl;
  	}else{
  		cout << "No such diet." << endl;
  	}
}

int main(){

	while(1){
		cin >> n >> m;

		if(n == 0 && m == 0)
			break;

		testcase(n, m);
	}

	return 0;
}