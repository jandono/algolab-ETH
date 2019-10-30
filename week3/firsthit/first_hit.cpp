/*
	After the first intersection transform the ray into a segment.
	This dramatically decreases the amount of constructions made.
*/

#include <iostream>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel K;

double floor_to_double(const K::FT &x){

	double a = floor(CGAL::to_double(x));
	while(a > x) a -= 1;
	while(a+1 <= x) a += 1;
	return a;
}

K::Point_2 source, direction, p1, p2, min_point;
K::Ray_2 r;
K::FT mini_dist, dist, dist_p1, dist_p2;
K::Segment_2 s, r_segment;
pair<K::Point_2, K::Point_2> segments[30001];
bool do_intersect;

int main(){
	ios_base::sync_with_stdio(false);

	long long x1, y1, x2, y2;
	int n;
	cout << setiosflags(ios::fixed) << setprecision(0);
	while(1){
		cin >> n;
		if(n==0)
			break;

		cin >> x1 >> y1 >> x2 >> y2;
		source = K::Point_2(x1, y1);
		direction = K::Point_2(x2, y2);
		r = K::Ray_2(source, direction);

		K::FT mini_dist;
		K::Point_2 min_point;
		bool flag_init = false;

		for(int i=0;i<n;i++){
			cin >> x1 >> y1 >> x2 >> y2;

			p1 = K::Point_2(x1, y1);
			p2 = K::Point_2(x2, y2);
			s = K::Segment_2(p1, p2);
			segments[i] = {p1, p2};
		}

		random_shuffle(segments, segments + n);

		for(int i=0;i<n;i++){
			p1 = segments[i].first;
		 	p2 = segments[i].second;
			s = K::Segment_2(p1, p2);

			if(flag_init)
				do_intersect = CGAL::do_intersect(r_segment, s);
			else
				do_intersect = CGAL::do_intersect(r, s);

			if(do_intersect){
				auto o = CGAL::intersection(r, s);

				if(const K::Point_2* op = boost::get<K::Point_2>(&*o)){
					// cout << "INTERSECTION POINT" << endl;
					dist = CGAL::squared_distance(source, *op);

					if(!flag_init){
						flag_init = true;
						mini_dist = dist;
						min_point = *op;
						r_segment = K::Segment_2(source, min_point);
					}else{
						if(dist < mini_dist){
							mini_dist = dist;
							min_point = *op;
							r_segment = K::Segment_2(source, min_point);
						}
					}
				}else
				if(const K::Segment_2* os = boost::get<K::Segment_2>(&*o)){
					// cout << "INTERSECTION SEGMENT" << endl;
					dist_p1 = CGAL::squared_distance(source, p1);
					dist_p2 = CGAL::squared_distance(source, p2);
					
					if(!flag_init){
						flag_init = true;
						mini_dist = dist_p1;
						min_point = p1;

						if(dist_p2 < mini_dist){
							mini_dist = dist_p2;
							min_point = p2;
						}

						r_segment = K::Segment_2(source, min_point);
					}else{
						if(dist_p1 < mini_dist){
							mini_dist = dist_p1;
							min_point = p1;
							r_segment = K::Segment_2(source, min_point);
						}

						if(dist_p2 < mini_dist){
							mini_dist = dist_p2;
							min_point = p2;
							r_segment = K::Segment_2(source, min_point);
						}
					}
				}
			}
		}

		if(!flag_init)
			cout << "no\n";
		else
			cout << floor_to_double(min_point.x()) << " " << floor_to_double(min_point.y()) << "\n";
	}

	return 0;
}