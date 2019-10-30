/*
	Min-max DP technique.
*/

#include <iostream>
#include <map>

using namespace std;
typedef pair<int, int> ii;

int n, coin[2500], dp1[2500][2500], dp2[2500][2500];
int p1, p2;

int solve_p1(int a, int b);
int solve_p2(int a, int b);

void test_case(){
	cin >> n;

	for(int i=0;i<n;i++){
		cin >> coin[i];
		for(int j=0;j<n;j++){
			dp1[i][j] = -1;
			dp2[i][j] = -1;
		}
	}

	p1 = solve_p1(0, n-1);

	cout << p1 << endl;
}

int main(){
	ios_base::sync_with_stdio(false);

	int T;
	cin >> T;
	while(T--) test_case();

	return 0;
}

int solve_p1(int i, int j){

	if(dp1[i][j] != -1)
		return dp1[i][j];

	if(i==j){
		dp1[i][j] = coin[i];
		return dp1[i][j];
	}

	dp1[i][j] = max(coin[i] + solve_p2(i+1, j), coin[j] + solve_p2(i, j-1));
	return dp1[i][j];
}

int solve_p2(int i, int j){

	if(dp2[i][j] != -1)
		return dp2[i][j];
	
	if(i==j){
		dp2[i][j] = 0;
		return dp2[i][j];
	}

	dp2[i][j] = min(solve_p1(i+1, j), solve_p1(i, j-1));
	return dp2[i][j];
}