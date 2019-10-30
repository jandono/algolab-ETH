/*
	DP[i][j] = Can I make modolu j using a subset of the first i cilinders.
*/

#include <iostream>
#include <vector>

using namespace std;

typedef vector<int> vi;

int n, mod, k;
vi heights;

void read_testcase(){

	cin >> n >> mod >> k;

	heights = vi(n);
	for(int i=0;i<n;i++){
		cin >> heights[i];
		heights[i] %= k;
	}
}

void solve_testcase(){
	bool dp[n][k];

	for(int i=0;i<n;i++){
		for(int j=0;j<k;j++){
			dp[i][j] = 0;
		}
	}

	dp[0][heights[0]] = true;
	if(dp[0][mod]){
		cout << "yes" << endl;
		return;
	}

	for(int i=1;i<n;i++){
		for(int j=0;j<k;j++){
			
			if(dp[i-1][j]){
				dp[i][j] = 1;
				dp[i][(j + heights[i]) % k] = 1;
			}

			if(dp[i][mod]){
				cout << "yes" << endl;
				return;
			}
		}
	}

	cout << "no" << endl;
}

void testcase(){

	read_testcase();
	solve_testcase();
}

int main(){
	ios_base::sync_with_stdio(false);
	int T; 
	cin >> T; 
	while(T--) testcase();

	return 0;
}