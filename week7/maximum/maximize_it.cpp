/*
	Solve maximization by negating the objective function while keeping the constraints constant.
	In set_d always multiply the coefficients with 2.
	Replace variables with new variables if needed (for example z^2 = w. Add w >=0 if degree is even).
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

double ceil_to_double(const SolT& x){
	double a = std::ceil(CGAL::to_double(x));
	while(a < x) a += 1;
	while(a-1 >= x) a -= 1;
	return a;
}

void solve_max(int a, int b){
	// max b · y − a · x^2         ==           min -b · y + a · x^2y 
	// x, y ≥ 0
	// x + y ≤ 4
	// 4x + 2y ≤ ab
	// − x + y ≤ 1

	Program qp(CGAL::SMALLER, false, 0, false, 0);

	const int X = 0;
	const int Y = 1;
	qp.set_a(X, 0, -1);	qp.set_a(Y, 0, -1); qp.set_b(0, 0);
	qp.set_a(X, 1, 1);	qp.set_a(Y, 1, 1); 	qp.set_b(1, 4);
	qp.set_a(X, 2, 4);	qp.set_a(Y, 2, 2); 	qp.set_b(2, a*b);
	qp.set_a(X, 3, -1);	qp.set_a(Y, 3, 1); 	qp.set_b(3, 1);
	qp.set_c(Y, -b);
	qp.set_d(X, X, 2*a);

	// solve the program, using ET as the exact type
	Solution s = CGAL::solve_quadratic_program(qp, ET());
  	assert (s.solves_quadratic_program(qp));

	// output solution
  	if(s.is_optimal()){
  		double val = floor_to_double(-1 * s.objective_value());
  		cout << val << endl;
  	}else
  	if(s.is_unbounded()){
  		cout << "unbounded" << endl;
  	}else{
  		cout << "no" << endl;
  	}
}

void solve_min(int a, int b){
	// min a · x^2 + b · y + z^4
	// x, y ≤ 0
	// x + y ≥ −4
	// 4x + 2y + z^2 ≥ −ab
	// − x + y ≥ −1
	
	Program qp(CGAL::LARGER, false, 0, true, 0);

	const int X = 0;
	const int Y = 1;
	const int Z = 2;

	qp.set_a(X, 0, 1);	qp.set_a(Y, 0, 1);	qp.set_b(0, -4);
	qp.set_a(X, 1, 4);	qp.set_a(Y, 1, 2);	qp.set_a(Z, 1, 1); qp.set_b(1, -a*b); // z = z^2
	qp.set_a(X, 2, -1);	qp.set_a(Y, 2, 1);	qp.set_b(2, -1);

	qp.set_l(Z, true, 0);
	qp.set_u(Z, false, 0);

	qp.set_d(X, X, 2*a);
	qp.set_d(Z, Z, 2);
	qp.set_c(Y, b);

	// solve the program, using ET as the exact type
	Solution s = CGAL::solve_quadratic_program(qp, ET());
  	assert (s.solves_quadratic_program(qp));

	// output solution
  	if(s.is_optimal()){
  		double val = ceil_to_double(s.objective_value());
  		cout << val << endl;
  	}else
  	if(s.is_unbounded()){
  		cout << "unbounded" << endl;
  	}else{
  		cout << "no" << endl;
  	}
}

void testcase(int p, int a, int b){

	if(p == 1)
		solve_max(a, b);
	else
		solve_min(a, b);
}

int main(){
	int p, a, b;
	cout << setprecision(100);
	while(1){
		cin >> p >> a >> b;

		if(!p) break;

		testcase(p, a, b);
	}
	return 0;
}