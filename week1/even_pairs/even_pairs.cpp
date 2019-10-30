/*
	Approach 1: 
		Partial sums trick
		Running time: O(n^2)

	Approach2:
		Dynamic programming approach.
		even[i] = even sums ending at position i
		result = sum(even)
		Running time: O(n)
*/


#include <iostream>

using namespace std;

int T, n, a;//[50001];

int main(){

	ios_base::sync_with_stdio(false);

	// cin >> T;
	// for(int t=0;t<T;t++){

	// 	cin >> n;
	// 	int sums[n+1];
	// 	sums[0] = 0;
	// 	for(int i=0;i<n;i++){
	// 		cin >> a[i];
	// 		sums[i+1] = sums[i] + a[i];
	// 	}

	// 	int counter = 0;
	// 	for(int i=1;i<=n;i++){
	// 		for(int j=i;j<=n;j++){
	// 			if((sums[j] - sums[i-1]) % 2 ==0){
	// 				// cout << sums[j] << " " << sums[i-1] << endl;
	// 				counter++;
	// 			}
	// 		}
	// 	}

	// 	cout << counter << endl;
	// }

	cin >> T;
	for(int t=0;t<T;t++){
		cin >> n;
		int ev = 0;
		int even[n+1]; even[0] = 0;
		int odd[n+1]; odd[0] = 0;
		for(int i=0;i<n;i++){
			cin >> a;

			if(a % 2 == 0){
				even[i+1] = even[i] + 1;
				odd[i+1] = odd[i];
			}else{
				even[i+1] = odd[i];
				odd[i+1] = even[i] + 1;
			}

			ev += even[i + 1];
		}

		cout << ev << endl;
	}

	return 0;
}