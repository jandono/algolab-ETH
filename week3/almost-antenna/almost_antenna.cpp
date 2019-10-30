/*
	The outlier must be one of the supporting points.
*/

#include <iostream>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
#include <set>

using namespace std;

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

vector<SK::Point_2> citizen;

int main(){
	ios_base::sync_with_stdio(false);

	int t, n;
	double x, y;
	while(1){
		cin >> n;
		if(!n)
			break;
		citizen.clear();

		for(int i=0;i<n;i++){
			cin >> x >> y;
			citizen.push_back(SK::Point_2(x,y));
		}

		SK::FT min_squared_radius, max_distance = -1, sq_dist;
		bool init_flag = false;

		Min_circle mc(citizen.begin(), citizen.end(), true);
		SK::Point_2 center = mc.circle().center();

		for(auto it = mc.support_points_begin(); it!=mc.support_points_end(); it++){
			SK::Point_2 t = *it;
			vector<SK::Point_2>::iterator position = find(citizen.begin(), citizen.end(), t);
			if (position != citizen.end()){ // == citizen.end() means the element was not found
			    iter_swap(position, citizen.end()-1);
			    citizen.pop_back();
			}

			Min_circle mc_tmp(citizen.begin(), citizen.end(), true);
			SK::FT squared_radius = mc_tmp.circle().squared_radius();

			if(!init_flag){
				min_squared_radius = squared_radius;
				init_flag = true;
			}
			else
			if(squared_radius < min_squared_radius)
				min_squared_radius = squared_radius;

			citizen.push_back(t);
		}

	  	cout << (long long)ceil_to_double(CGAL::sqrt(min_squared_radius)) << "\n";
	}
	return 0;
}