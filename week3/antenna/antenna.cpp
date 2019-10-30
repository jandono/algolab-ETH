/*
	Minimum enclosing circle.
*/

#include <iostream>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
#include <cmath>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt SK;
typedef  CGAL::Min_circle_2_traits_2<SK>  	Traits;
typedef  CGAL::Min_circle_2<Traits>     	Min_circle;

double ceil_to_double(const SK::FT& x)
{
	double a = std::ceil(CGAL::to_double(x));
	while (a<x) a += 1;
	while (a-1 >= x) a -= 1;
	return a;
}

SK::Point_2 citizen[200001];

int main(){
	std::ios_base::sync_with_stdio(false);

	int t, n;
	double x, y;
	while(1){
		std::cin >> n;
		if(!n)
			break;

		for(int i=0;i<n;i++){
			std::cin >> x >> y;
			citizen[i] = SK::Point_2(x, y);
		}

		Min_circle mc(citizen, citizen+n, true);
	  	Traits::Circle c = mc.circle();
	  	std::cout << (long long)ceil_to_double(CGAL::sqrt(c.squared_radius())) << "\n";
	}
	return 0;
}