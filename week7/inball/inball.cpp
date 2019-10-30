/*
	For each constraint, given a center and a radius we want the point on the 
	hyperball surface in the direction of the vector defining the hyperplane 
	constraint, to be whithin the desired boundaries.
	Given a center C E R^d and a radius R E R, and a hyperplane vector a E R^d 
	we calculate that point by the equation:

		C + R * a / ||a||

	Therefore the constraints we get are:

		a_i^T * C + R * ||a_i|| <= b_i

	So the overall program becomes:

	min 	-r

	s.t.	a_00 * c_0 + ... + a_0d-1 * c_d-1 + r * ||a_0|| <= b_0
			.
			.
			.
			a_n0 * c_0 + ... + a_nd-1 * c_d-1 + r * ||a_n|| <= b_n

			r >= 0
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

void testcase(int n, int d){

	int a_ij, b_i;

	Program lp(CGAL::SMALLER, false, 0, false, 0);

	for(int i=0;i<n;i++){

		double length = 0;
		for(int j=0;j<d;j++){

			cin >> a_ij;
			lp.set_a(j, i, a_ij);

			length += a_ij * a_ij;
		}

		lp.set_a(d, i, floor(sqrt(length)));


		cin >> b_i;
		lp.set_b(i, b_i);
	}
	// lp.set_a(d, n, 1);	
	// lp.set_b(n, 0);
	// lp.set_r(n, CGAL::LARGER);
	lp.set_l(d, true, 0);
	lp.set_c(d, -1);

	Solution s = CGAL::solve_linear_program(lp, ET());
	assert(s.solves_linear_program(lp));

	if(s.is_infeasible()){
		cout << "none" << endl;
	}else
	if(s.is_unbounded()){
		cout << "inf" << endl;
	}else{
		cout << floor_to_double(-s.objective_value()) << endl;
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	int n, d;
	while(1){
		cin >> n;
		if(!n)
			break;
		cin >> d;
		testcase(n, d);
	}
	return 0;
}