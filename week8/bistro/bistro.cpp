/*
	Nearest vertex returns a vertex handle.
	The squared distance is always an integer.
*/

#include <iostream>
#include <vector>
#include <climits>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt EK;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;

using namespace std;

long long n, m, x, y;
vector<K::Point_2> points;

void read_testcase(){

	points = vector<K::Point_2>(n);
	for(int i=0;i<n;i++){
		cin >> x >> y;
		points[i] = K::Point_2(x, y);
	}
}

void solve_testcase(){
	Triangulation t;
	t.insert(points.begin(), points.end());

	cin >> m;
	for(int i=0;i<m;i++){

		cin >> x >> y;
		Triangulation::Vertex_handle vh = t.nearest_vertex(K::Point_2(x, y));
		cout << (long long)CGAL::squared_distance(K::Point_2(x, y), vh->point()) << endl;
	}
}

void testcase(){

	read_testcase();
	solve_testcase();
}


int main(){

	ios_base::sync_with_stdio(false);

	while(1){
		cin >> n;
		if(!n) break;
		testcase();
	}

	return 0;
}