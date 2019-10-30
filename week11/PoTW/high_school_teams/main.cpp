/*
	Split and list with more than 2 possibilities.
	Use backtracking for creating the possibilities.
	Add every possibility of the first split in a vector.
	Add every possibility of the second split in a vector.
	Sort the second vector.
	For every element in the first vector:
		use lower_bound to get the first element >= than what we are looking.
		use upper_bound to get the first element > than what we are looking.
		the difference is the amount of elements that satisfy our condition.
*/

#include <iostream>
#include <bitset>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <assert.h>
#include <boost/functional/hash.hpp>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> ii;

ll n, k, counter, half, other_half;
vector<ll> student;

void read_testcase(){

	cin >> n >> k;
	student = vector<ll>(n);
	for(int i=0;i<n;i++){
		cin >> student[i];
	}

	half = n/2;
	other_half = n - half;
}

void create_teams(ll curr, ll lbound, ll ubound, vector<ll> &teams, vector<ii> &possibilities){

	if(curr == ubound){
		ll sum_team1 = 0, sum_team2 = 0, not_playing = 0;
		
		for(int i=0;i<teams.size();i++){

			if(teams[i] == 1)
				sum_team1 += student[i + lbound];
			else
			if(teams[i] == 2)
				sum_team2 += student[i + lbound];
			else
				not_playing++;

			if(not_playing > k)
				return;
		}

		possibilities.push_back({sum_team1 - sum_team2, not_playing});
		return;
	}

	for(int i=0;i<3;i++){
		teams.push_back(i);
		create_teams(curr + 1, lbound, ubound, teams, possibilities);
		teams.pop_back();
	}
}

void solve_testcase(){

	counter = 0;
	vector<ll> teams;
	vector<ii> possibilities1;
	create_teams(0, 0, half, teams, possibilities1);

	teams = vector<ll>();
	vector<ii> possibilities2;
	create_teams(half, half, n, teams, possibilities2);

	sort(possibilities2.begin(), possibilities2.end());

	for(auto el : possibilities1){

		ii lookup_low = {-el.first, 0};
		ii lookup_high = {-el.first, k - el.second};

		//first thing >= than what I am looking for
		vector<ii>::iterator low = lower_bound(possibilities2.begin(), possibilities2.end(), lookup_low);

		//first thing > than what I am looking for
		vector<ii>::iterator high = upper_bound(possibilities2.begin(), possibilities2.end(), lookup_high);

		counter += high - low;
	}

	cout << counter << endl;
}

void test_case(){
	read_testcase();
	solve_testcase();
}

int main(){
	std::ios_base::sync_with_stdio(false);
	int T; std::cin >> T; while(T--) test_case();
	return 0;
}