/*
    Iterate over edges of the triangulation.
    Find the smallest distance.
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
typedef Triangulation::Edge_iterator  Edge_iterator;

long long n, x, y;
std::vector<K::Point_2> points;

double ceil_to_double(const EK::FT& x)
{
 double a = std::ceil(CGAL::to_double(x));
 while (a < x) a += 1;
 while (a-1 >= x) a -= 1;
 return a;
}

void read_testcase(int n){

    points.clear();

    for(int i=0;i<n;i++){
        std::cin >> x >> y;
        points.push_back(K::Point_2(x, y));
    }
}

void solve_testcase(){

    Triangulation t;
    t.insert(points.begin(), points.end());

    EK::FT min_dist = -1;
    for (Edge_iterator e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e){

        if(min_dist == -1 || (t.segment(e).squared_length() < min_dist)){
            min_dist = t.segment(e).squared_length();
        }
    }

    std::cout << ceil_to_double(50 * sqrt(min_dist)) << std::endl;
}

void testcase(int n){
    read_testcase(n);
    solve_testcase();
}

int main(){
    std::ios_base::sync_with_stdio(false);

    while(1){
        std::cin >> n;
        if(!n)
            break;

        testcase(n);
    }
    return 0;
}
