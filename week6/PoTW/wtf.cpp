#include <iostream>
#include <tuple>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#include <algorithm>
#include <boost/functional/hash.hpp>

using namespace std;

int m[5], n, c;
vector<long long> chips[5];
// map<vector<long long>, long long> solution;
unordered_map<vector<long long>, long long, boost::hash<vector<long long> > > solution;


void read_test_case(){
	cin >> n;
	for(int i=0;i<n;i++){
		cin >> m[i];
		chips[i].clear();
	}

	for(int i=0;i<n;i++){
		for(int j=0;j<m[i];j++){
			cin >> c;
			chips[i].push_back(c);
		}
	}
}

bool done(vector<long long> state){
	bool zeros = true;
	for(int i=0;i<n;i++){
		if(state[i] < 0)
			return true;

		if(state[i] > 0)
			zeros = false;
	}

	if(zeros)
		return true;

	return false;
}

long long solve(vector<long long> state){

	if(solution.count(state))
		return solution[state];

	// if(done(state)){
	// 	solution[state] = 0;
	// 	return solution[state];
	// }

	solution[state] = 0;

	int limit = 1 << n;
	for(int combination=0;combination<limit;combination++){

		vector<long long> temp_state;
		for(int tmp=0;tmp<n;tmp++){
			temp_state.push_back(state[tmp]);
		}

		set<long long> colors; int points=0;
		for(int j=0;j<n;j++){

			if(combination & 1<<j && temp_state[j]>=0){
				colors.insert(chips[j][temp_state[j]]);
				temp_state[j]--;
				points++;
			}
		}

		if(colors.size()==1){

			if(points > 1)
				solution[state] = max(solution[state], (long long)pow(2, points-2) + solve(temp_state));
			else
				solution[state] = max(solution[state], solve(temp_state));
		}
	}

	return solution[state];
}

void test_case(){

	read_test_case();
	solution.clear();
	vector<long long> state;
	for(int i=0;i<n;i++){
		state.push_back(chips[i].size()-1);
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