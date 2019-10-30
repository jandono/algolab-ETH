/*
	Similar to Even Pairs just instead of adding numbers
	we add columns and keep track of the even sums each new 
	column creates.

	Running time: O(n^3)
*/

#include <iostream>

using namespace std;

int T, a[201][201], n, columns_sum[201][201];

int main(){

	ios_base::sync_with_stdio(false);

	cin >> T;

	for(;T>0;T--){

		cin >> n;

		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				cin >> a[i][j];

		for(int i=0;i<=n;i++){
			columns_sum[0][i] = 0;
			columns_sum[i][0] = 0;
		}

		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				columns_sum[i][j] = columns_sum[i-1][j] + a[i-1][j-1];
			}
		}

		int even = 0;
		for(int i1=1;i1<=n;i1++){
			for(int i2=i1;i2<=n;i2++){

				int sol_1d = 0;
				int even_1d = 0; // even sums ending at k
				int odd_1d = 0;  // odd sums ending at k
				
				for(int k=1;k<=n;k++){
					int col = columns_sum[i2][k] - columns_sum[i1-1][k];

					if(col % 2 == 0){
						even_1d = even_1d + 1;
						// odd_1d = odd_1d;
					}else{
						int t = odd_1d;
						odd_1d = even_1d + 1;
						even_1d = t;
					}

					sol_1d += even_1d;
				}

				even += sol_1d;
			}
		}

		cout << even << endl;
	}	
	
	return 0;
}