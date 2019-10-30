#include <iostream>
#include <climits>
#include <unordered_set>

using namespace std;

int T, n, k, max_vol, vol[100], cost[100], dp[20000], liters[20000];
int knapsack_limit, solution_cost, solution_distinct, curr;
unordered_set<int> distinct[20000];

void read_testcase(){

	cin >> n >> k;
	max_vol = -1;
	for(int i=0; i<n; i++){
		cin >> cost[i] >> vol[i];
		max_vol = max(max_vol, vol[i]);
	}
}

void solve(){

	knapsack_limit = k + max_vol;
	dp[0] = 0;
	for(int i=1; i<knapsack_limit; i++){

		distinct[i].clear();

		dp[i] = INT_MAX;

		for(int j=0; j<n; j++){
			
			if(vol[j] > i)
				continue;

			curr = cost[j] + dp[i - vol[j]];

			if(curr < dp[i]){

				dp[i] = curr;
				liters[i] = vol[j] + liters[i - vol[j]];
				distinct[i] = distinct[i - vol[j]];
				distinct[i].insert(j);
			}else
			if(curr == dp[i]){
				liters[i] = max(liters[i], vol[j] + liters[i - vol[j]]);

				if(!distinct[i - vol[j]].count(j) + distinct[i - vol[j]].size() > distinct[i].size()){

					distinct[i] = distinct[i - vol[j]];
					distinct[i].insert(j);
				}
			}
		}

		if(dp[i] == INT_MAX)
			dp[i] = 0;
	}

	// for(int i=0; i<knapsack_limit; i++){
	// 	cout << "#######################" << endl;
	// 	cout << "Size: " << i << " | Filled: " << liters[i] << "| Cost: " << dp[i] << endl;
	// 	cout << "Elements used: ";
	// 	for(auto el : distinct[i])
	// 		cout << el << ", ";
	// 	cout << endl;
	// }

	solution_cost = INT_MAX;
	solution_distinct = 0;
	for(int i=k; i < knapsack_limit; i++){

		if(liters[i] < k)
			continue;

		if(dp[i] < solution_cost){

			solution_cost = dp[i];
			solution_distinct = distinct[i].size();
		}
		// else
		// if(dp[i] == solution_cost && distinct[i].size() < solution_distinct){
		// 	solution_distinct = distinct[i].size();
		// }
	}

	cout << solution_cost << " " << solution_distinct << endl;
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