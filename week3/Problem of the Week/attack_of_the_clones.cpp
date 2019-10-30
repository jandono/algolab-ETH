/*
	1. Find minimum overlaping point in O(N) time.
	2. Reposition all intervals accordingly such that minimum overlaping
	   point = 0
	3. Either don't choose any, or choose only 1 of the overlaping intervals 
	   at 0. 
	4. Solve greedy by sorting the intervals by right coordinate
*/


#include <iostream>
#include <algorithm>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<long, long> ii;
long T, n, m, a_i, b_i, min_olap_point, min_olap;
vector<ii> intervals, points, overlaps, intervals_processed;

bool comparator_second_asc(const ii &left, const ii &right){
	if(left.second==right.second)
		return left.first < right.first;
	return left.second < right.second;
}

bool comparator_points(const ii &left, const ii &right){
	if(left.first==right.first)
		return left.second > right.second;
	return left.first < right.first;
}

void read_intervals(){
	// read intervals
	for(int i=0;i<n;i++){
		cin >> a_i >> b_i; a_i--; b_i--;
		intervals.push_back({a_i, b_i});
	}
}

int find_min_overlapping(){

	long counter = 0;
	for(int i=0;i<intervals.size();i++){
		if(intervals[i].first > intervals[i].second)
			counter++;
		
		points.push_back({intervals[i].first, +1});
		points.push_back({intervals[i].second+1, -1});
	}
	sort(points.begin(), points.end(), comparator_points);

	int mini = counter, mini_pos = 0, j = 0;
	while(j<points.size()){
		counter += points[j].second;
		if(counter < mini){
			mini = counter;
			mini_pos = points[j].first;
		}
		j++;
	}

	return mini_pos;
}

void reposition_intervals(int offset){
	for(int i=0;i<intervals.size();i++){
		intervals[i].first -= offset;
		if(intervals[i].first < 0)
			intervals[i].first += m;

		intervals[i].second -= offset;
		if(intervals[i].second < 0)
			intervals[i].second += m; 
	}
}

void remove_overlaps(){
	for(int i=0;i<intervals.size();i++){
		
		if((intervals[i].first>intervals[i].second || intervals[i].first == 0 || 
			intervals[i].second == 0))
			overlaps.push_back(intervals[i]);
		else
			intervals_processed.push_back(intervals[i]);
	}
	sort(intervals_processed.begin(), intervals_processed.end(), comparator_second_asc);
}


void solve_greedy(){
	//solve greedy without taking an overlaping segment
	int right_point = 0, interval_counter = 0;
	for(int i=0;i<intervals_processed.size();i++){
		int curr_left = intervals_processed[i].first;
		int curr_right = intervals_processed[i].second;

		if(curr_left > right_point){
			interval_counter++;
			right_point = curr_right;
		}
	}

	//solve greedy by taking only one overlaping segment
	int maxi_interval_counter = interval_counter, m1;
	for(auto overlap : overlaps){

		right_point = overlap.second;
		interval_counter = 1;
		if(overlap.first > overlap.second)
			m1 = overlap.first-1;
		else
			m1 = m-1;

		for(int i=0;i<intervals_processed.size();i++){
			int curr_left = intervals_processed[i].first;
			int curr_right = intervals_processed[i].second;

			if(curr_left > right_point && curr_right <= m1){
				interval_counter++;
				right_point = curr_right;
			}
		}

		if(interval_counter > maxi_interval_counter)
			maxi_interval_counter = interval_counter;
	}
	cout << maxi_interval_counter << "\n";
}

void init_test_case(){
	intervals.clear();
	intervals_processed.clear();
	points.clear();
	overlaps.clear();
}

void solve_test_case(){
	
	init_test_case();
	cin >> n >> m;
	read_intervals();
	int min_olap_point = find_min_overlapping();
	reposition_intervals(min_olap_point);
	remove_overlaps();
	solve_greedy();
}

int main(){
	ios_base::sync_with_stdio(false);

	cin >> T;
	while(T--){
		solve_test_case();
	}

	return 0;
}