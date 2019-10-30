/*
	CGAL's QP solver can only solve quadratic objective functions and linear constraints.
	Therefore whenever we encounter nonlinear constraints, we need to transform the problem
	either in a way where we don't explicitly use them or in a way where we use them as part
	of the objective function.
	For this problem we transform:

	max alpha_0 * r_0 + ... alpha_n-1 * r_n-1
	
	s.t.	
	Constraint 1:	alpha_0 * alpha_0 * v_00 + ... + alpha_0 * alpha_n * v_0n +
					.
					.
					.
					+ alpha_n * alpha_0 * v_n0 + ... + alpha_n * alpha_n * v_nn

	Constraint 2:	alpha_0 * c_0 + ... + alpha_n * c_n <= C
	Constraint 3:	alpha_0 * r_0 + ... + alpha_n * r_n >= R

	TO:

	min 	alpha_0 * alpha_0 * v_00 + ... + alpha_0 * alpha_n * v_0n +
			.
			.
			.
			+ alpha_n * alpha_0 * v_n0 + ... + alpha_n * alpha_n * v_nn
	
	s.t.	
	Constraint 2:	alpha_0 * c_0 + ... + alpha_n * c_n <= C
	Constraint 3:	alpha_0 * r_0 + ... + alpha_n * r_n >= R

	We can do this because all thats required to solve this is to find if a solution exist
	and we do not have to maximize the reward. Therefore we solve this QP and check for 
	feasibility. If feasible the last thing we need to check is if the objective function
	value is <= V.
*/

#include <iostream>
#include <cassert>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

using namespace std;

// choose exact integral type
typedef CGAL::Gmpq ET;

// program and solution types
typedef CGAL::Quotient<ET> SolT;
typedef CGAL::Quadratic_program<double> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

void testcase(int n, int m){

	int c_i, r_i, v_ij, C, R, V;

	Program qp(CGAL::SMALLER, true, 0, false, 0);

	for(int i=0;i<n;i++){

		cin >> c_i >> r_i;
		qp.set_a(i, 0, c_i);
		qp.set_a(i, 1, r_i);
	}

	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){

			cin >> v_ij;
			if(j <= i)
				qp.set_d(i, j, 2*v_ij);
		}
	}

	for(int i=0;i<m;i++){

		cin >> C >> R >> V;

		qp.set_b(0, C);
		qp.set_b(1, R);
		qp.set_r(1, CGAL::LARGER);

		// solve the program, using ET as the exact type
		Solution s = CGAL::solve_quadratic_program(qp, ET());
		assert(s.solves_quadratic_program(qp, ET()));

		// cout << s << endl;

		if(s.is_infeasible() || s.objective_value() > V){
			cout << "No." << endl;
		}else{
			cout << "Yes." << endl;
		}
	}
}

int main(){

	ios_base::sync_with_stdio(false);

	int n, m;

	while(1){
		cin >> n >> m;

		if(n == 0 && m == 0)
			break;

		testcase(n, m);
	}

	return 0;
}