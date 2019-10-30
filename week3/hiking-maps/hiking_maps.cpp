/*
	For each triangle find the segments in it.
	Use sliding window to obtain the best solution.
*/

#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <vector>
#include <cmath>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;

pair<P,P> segments[8000];
int t, n, m;
long long x, y, x2, y2;
P line_points[6];
vector<int> segments_in_triangle[8000];
const P *op;

int main(){
	std::ios_base::sync_with_stdio(false);

	cin >> t;
	while(t--){

		cin >> m >> n;

		//read paths
		cin >> x >> y;
		for(int i=1;i<m;i++){
			cin >> x2 >> y2;
			segments[i-1] = {P(x, y), P(x2, y2)};
			x = x2;
			y = y2;
		}

		//read triangles
		for(int i=0;i<n;i++){
			segments_in_triangle[i].clear();
			for(int j=0;j<6;j++){
				cin >> x >> y;
				line_points[j] = P(x, y); 
			}

			for (int j = 0; j < 6; j+=2)
				if (CGAL::right_turn(line_points[j],line_points[j+1],line_points[(j+2)%6])) 
				{
					P t = line_points[j];
					line_points[j] = line_points[j+1];
					line_points[j+1] = t;
				}	

			for(int j=0;j<m-1;j++){

				if(!CGAL::right_turn(line_points[0], line_points[1], segments[j].first) &&
					!CGAL::right_turn(line_points[2], line_points[3], segments[j].first) &&
					!CGAL::right_turn(line_points[4], line_points[5], segments[j].first) &&
					!CGAL::right_turn(line_points[0], line_points[1], segments[j].second) &&
					!CGAL::right_turn(line_points[2], line_points[3], segments[j].second) &&
					!CGAL::right_turn(line_points[4], line_points[5], segments[j].second))
					segments_in_triangle[i].push_back(j);
			}
		}

		//obtain best solution by using a sliding window
		int diff = 0;
		int s = 0;
		int e = 0;
		int leg_counter = 0;
		map<int, int> curr_segments;
		int solution = INT_MAX;
		bool found;
		while(1){

			found = false;
			while(leg_counter < m-1 && e < n){
				for(int i=0;i<segments_in_triangle[e].size();i++){
					int curr_segment = segments_in_triangle[e][i];
					if(curr_segments.count(curr_segment) && curr_segments[curr_segment]!=0){
						curr_segments[curr_segment]++;
					}
					else{
						curr_segments[curr_segment] = 1;
						leg_counter++;
					}
				}
				e++;
			}

			if(leg_counter >= m-1)
				found = true;

			while(leg_counter >= m-1 && s < e){
				for(int i=0;i<segments_in_triangle[s].size();i++){
					int curr_segment = segments_in_triangle[s][i];
					if(curr_segments[curr_segment] == 1){
						leg_counter--;
					}
					
					curr_segments[curr_segment]--;
				}
				s++;
			}

			if(found)
				solution = min(solution, e - s + 1);

			if(e == n && leg_counter < m-1)
				break;
		}

		cout << solution << "\n";
	}

	return 0;
}