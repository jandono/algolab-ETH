#include <iostream>

using namespace std;

int T, h, w;
char field[100][17], space;
bool available[100][17];
int dp[110][25];

void read_testcase(){

	cin >> h >> w;

	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
			cin >> field[i][j];

			if(i - 1 >= 0 && j - 1 >= 0){
				if(field[i][j] == '1' && field[i-1][j] == '1' && 
				   field[i][j-1] == '1' && field[i-1][j-1] == '1')
					available[i][j] = true;
				else
					available[i][j] = false;
			}else{
				available[i][j] = false;
			}
		}
	}

	// for(int i=0;i<h;i++){
	// 	for(int j=0;j<w-1;j++){
	// 		cout << available[i][j] << " ";
	// 	}
	// 	cout << available[i][w-1] << endl;
	// }
}

void solve(){

	for(int i=0;i<h;i++){
		dp[i][0] = 0;
		dp[i][1] = 0;
		dp[0][i] = 0;
		dp[1][i] = 0;
	}

	for(int i=2;i<h;i++){
		for(int j=2;j<h;j++){

			if(available[i][j]){

				dp[i][j] = max(1 + dp[i-2][j] + dp[i][j-2] - dp[i-2][j-2], 
							       dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1]);
			}else{
				dp[i][j] = dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1];
			}
		}
	}

	for(int i=0;i<h;i++){
		for(int j=0;j<w-1;j++){
			cout << dp[i][j] << " ";
		}
		cout << dp[i][w-1] << endl;
	}
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