/*
	Read  the parasols and sort them.
	Use sliding window and keep track of the current parsols in the window.
		If current count > max_count:
	 		update max_count, worst_distance and clear possible_solutions. 
			Insert the new solution.

		If current count == max_count:
			If current distance is better than worst_distance:
				Update worst_distance.
				Clear possible_solutions.
			If current distance is equal to worst_distance:
				Add solution(or two solutions if the distance is odd) to possible solutions.
*/


#include <iostream>
#include <unordered_map>
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;

int T, n, parasols[1000000];
unordered_map<int, int> m;
vector<int> possible_solutions;

void read_testcase(){

	cin >> n;
	for(int i=0;i<n;i++){
		cin >> parasols[i];
	}

	sort(parasols, parasols + n);
}

void solve(){
	possible_solutions.clear();

	int l = 0, r = 0, count = 0, max_count = -1, worst_distance = INT_MAX;
	while(r < n){

		int distance = parasols[r] - parasols[l];

		if(distance <= 200){
			count++;

			if(count > max_count){
				max_count = count;
				worst_distance = (distance + 1) / 2;
				possible_solutions.clear();
				
				possible_solutions.push_back(parasols[l] + distance / 2);
				if(distance % 2 == 1)
  					possible_solutions.push_back(parasols[l] + (distance + 1) / 2);
			}else
			if(count == max_count){

				if(worst_distance > (distance + 1) / 2){
					possible_solutions.clear();
					worst_distance = (distance + 1) / 2;
				}else
				if(worst_distance == (distance + 1) / 2){
					possible_solutions.push_back(parasols[l] + distance / 2);
					if(distance % 2 == 1)
	  					possible_solutions.push_back(parasols[l] + (distance + 1) / 2);
  				}
			}

			r++;
		}else{
			count--;
			l++;
		}
	}

	cout << max_count << " " << worst_distance << endl;
	for(int i=0;i<possible_solutions.size()-1;i++)
		cout << possible_solutions[i] << " ";
	cout << possible_solutions[possible_solutions.size()-1] << endl;
}

void testcase(){
	read_testcase();
	solve();
}

int main(){
	ios_base::sync_with_stdio(false);
	cin >> T;
	while(T--) testcase();
	return 0;
}