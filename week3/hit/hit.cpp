#include <iostream>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;

using namespace std;

int main(){
	
	ios_base::sync_with_stdio(false);
	long long x, y, a, b, n;
	while(1){
		cin >> n;
		if(n==0)
			break;

		cin >> x >> y >> a >> b;
		K::Point_2 source(x, y);
		K::Point_2 direction(a, b);
		K::Ray_2 r(source, direction);

		bool flag = false;
		for(int i=0;i<n;i++){
			cin >> x >> y >> a >> b;
			if(!flag){
				K::Point_2 p1(x, y);
				K::Point_2 p2(a, b);
				K::Segment_2 s(p1, p2);

				if(CGAL::do_intersect(r, s)){
					flag = true;
				}
			}
		}

		if(flag)
			cout << "yes\n";
		else
			cout << "no\n";
	}

	return 0;
}