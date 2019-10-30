/*
	Create a Triangulation and for each point calculate the closest obstacle to it.
	Then just use basic math to transform this to death_timers.
*/

#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt EK;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;

typedef K::Point_2 Point;

using namespace std;

long long n, l, b, r, t, x, y;
vector<Point> points;
map<Point, int> points_to_index;
vector<K::FT> dies;

double ceil_to_double(const EK::FT& x)
{
  double a = std::ceil(CGAL::to_double(x));
  while (a < x) a += 1;
  while (a-1 >= x) a -= 1;
  return a;
}

void read_testcase(){

	points_to_index.clear();
	points = vector<Point>(n);
	dies = vector<K::FT>(n);

	cin >> l >> b >> r >> t;

	for(int i=0;i<n;i++){

		cin >> x >> y;
		points[i] = Point(x, y);
		points_to_index[points[i]] = i;

		long long closest_wall = min(
			min(abs(x-l), abs(x-r)),
			min(abs(y-b), abs(y-t))
		);

		dies[i] = K::FT(closest_wall*closest_wall);
	}
}

void solve_testcase(){

	Triangulation t;
	t.insert(points.begin(), points.end());

	for(Edge_iterator e = t.finite_edges_begin(); e!= t.finite_edges_end(); e++){

		int u = points_to_index[t.segment(e).source()];
		int v = points_to_index[t.segment(e).target()];

		dies[u] = min(dies[u], t.segment(e).squared_length()/4);
		dies[v] = min(dies[v], t.segment(e).squared_length()/4);
	}

	sort(dies.begin(), dies.end());

	cout << ceil_to_double(sqrt(sqrt(EK::FT(dies[0])) - 0.5)) << " ";
	cout << ceil_to_double(sqrt(sqrt(EK::FT(dies[n/2])) - 0.5)) << " ";
	cout << ceil_to_double(sqrt(sqrt(EK::FT(dies[n-1])) - 0.5)) << endl;
}

void testcase(){
	read_testcase();
	solve_testcase();
}

int main(){
	ios_base::sync_with_stdio(true);

	while(1){
		cin >> n;
		if(!n) break;
		testcase();
	}
	return 0;
}