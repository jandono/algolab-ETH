/*
	Dynamic programming where the state is defined as
	the amount of chips in each pile.
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#include <algorithm>
#include <boost/functional/hash.hpp>

using namespace std;

int m[5], n;
int chips[5][2000];
unordered_map<vector<int>, int, boost::hash<vector<int> > > solution;

void read_test_case(){
	cin >> n;
	for(int i=0;i<n;i++){
		cin >> m[i];
	}

	for(int i=0;i<n;i++){
		for(int j=0;j<m[i];j++){
			cin >> chips[i][j];
		}
	}
}

int solve(const vector<int> &state){

	if(solution.count(state))
		return solution[state];

	solution[state] = 0;

	int limit = 1 << n;
	vector<int> new_state(n);

	for(int combination=1;combination<limit;combination++){

		int color=-1; int points=0;
		for(int j=0;j<n;j++){
			new_state[j] = state[j];
			if(new_state[j]>=0 && combination & 1<<j){
				if(color == -1){
					color = chips[j][new_state[j]];
				}else
				if(color != chips[j][new_state[j]]){
					color = -1;
					break;
				}
				new_state[j]--;
				points++;
			}
		}

		if(color!=-1){

			if(points > 1)
				solution[state] = max(solution[state], (int)pow(2, points-2) + solve(new_state));
			else
				solution[state] = max(solution[state], solve(new_state));
		}
	}

	return solution[state];
}

void test_case(){

	read_test_case();
	solution.clear();
	vector<int> state;
	for(int i=0;i<n;i++){
		state.push_back(m[i]-1);
	}

	int solution = solve(state);
	cout << solution << endl;
}

int main(){
	ios_base::sync_with_stdio(false);

	int T;
	cin >> T;

	while(T--) test_case();

	return 0;
}