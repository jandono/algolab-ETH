#include <iostream>

typedef std::pair<int,int> ii;
int T, n, a[151][151], dp_down[151][151], dp_up[151][151];

void read_testcase(){

	std::cin >> n;
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			std::cin >> a[i][j];
}

void solve(){

	dp_down[0][0] = a[0][0];
	for(int i=1;i<n;i++){
		dp_down[0][i] = dp_down[0][i-1] + a[0][i];
		dp_down[i][0] = dp_down[i-1][0] + a[i][0];
	}

	for(int i=1;i<n;i++){
		for(int j=1;j<n;j++){
			dp_down[i][j] = std::max(dp_down[i-1][j], dp_down[i][j-1]) + a[i][j];
		}
	}

	int i1 = n-1, j1 = n-1;
	while(i1 != 0 && j1 != 0){
		a[i1][j1] = 0;

		if(i1 > 0 && j1 > 0){
			if(dp_down[i1-1][j1] > dp_down[i1][j1-1])
				i1--;
			else
				j1--;
		}else
		if(i1 > 0)
			i1--;
		else
			j1--;
	}

	dp_up[n-1][n-1] = a[n-1][n-1];
	for(int i=n-2;i>=0;i--){
		dp_up[n-1][i] = dp_up[n-1][i+1] + a[n-1][i];
		dp_up[i][n-1] = dp_up[i+1][n-1] + a[i][n-1];
	}

	for(int i=n-2;i>=0;i--){
		for(int j=n-2;j>=0;j--){
			dp_up[i][j] = std::max(dp_up[i+1][j], dp_up[i][j+1]) + a[i][j];
		}
	}

	std::cout << dp_down[n-1][n-1] + dp_up[0][0] << std::endl;
}

void testcase(){

	read_testcase();
	solve();
}

int main(){
	std::ios_base::sync_with_stdio(false);

	std::cin >> T;
	while(T--) testcase();
	return 0;
}