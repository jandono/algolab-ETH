/*
	Get the valid intervals using sliding window in O(N) time.
	Keep the intervals by keeping their right coordinate and length:
		intervals[right_coordinate] = length

	Do a DP such that dp[i][j] = best solution by looking at the first i defenders and using j attackers.
	
	dp[i][j] = max(dp[i - intervals[i]][j-1] + intervals[i], dp[i-1][j]);
*/

#include <iostream>
#include <vector>

using namespace std;

int T, n, m, k, defense_line[100000], sum;
int dp[100000][101];
vector<int> intervals;

void read_testcase(){
	cin >> n >> m >> k;

	for(int i=0;i<n;i++){
		cin >> defense_line[i];
	}
}

void solve_intervals(){

	int l = 0, r = 0;
	intervals = vector<int>(n, 0);
	sum = defense_line[0];

	while(l < n && r < n){
		if(sum < k){
			r++;
			sum += defense_line[r];
		}else
		if(sum > k){
			sum -= defense_line[l];
			l++;
		}else{
			intervals[r] = r - l + 1;
			sum -= defense_line[l];
			l++;
		}
	}
}

void solve_dp(){

	for(int i=0;i<n;i++){
		dp[i][0] = 0;
	}

	for(int j=1;j<=m;j++){
		dp[0][j] = intervals[0];
	}

	for(int i=1;i<n;i++){
		for(int j=1;j<=m;j++){

			if(!intervals[i]){
				dp[i][j] = dp[i-1][j];
			}else
			if(i - intervals[i] >= 0)
				dp[i][j] = max(dp[i - intervals[i]][j-1] + intervals[i], dp[i-1][j]);
			else
				dp[i][j] = max(intervals[i], dp[i-1][j]);
		}
	}

	if(dp[n-1][m] > dp[n-1][m-1])
		cout << dp[n-1][m] << endl;
	else
		cout << "fail" << endl;
}

void testcase(){
	read_testcase();
	solve_intervals();
	solve_dp();
}

int main(){
	ios_base::sync_with_stdio(false);
	cin >> T;
	while(T--) testcase();
	return 0;
}