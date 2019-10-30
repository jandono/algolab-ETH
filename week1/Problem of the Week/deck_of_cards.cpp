/*
	Sliding window technique.
	Running time: O(n)
*/

#include <iostream>
#include <climits>

using namespace std;

int T, n;
long long cards[100001], k;
long long sum, mini;

int main(){

	ios_base::sync_with_stdio(false);

	cin >> T;
	for(int t=0;t<T;t++){
		cin >> n >> k;

		for(int i=0;i<n;i++){
			cin >> cards[i];
		}

		int i=0, j=0, mini_i, mini_j;
		sum = cards[i];
		mini = LLONG_MAX;

		while(i<n && j<n){

			if(abs(k-sum) < mini){

				mini = abs(k-sum);
				mini_i = i;
				mini_j = j;
			}

			if(sum < k){
				j++;
				sum += cards[j];
			}else{
				sum -= cards[i];
				i++;
			}
		}

		cout << mini_i << " " << mini_j << endl;
	}

	return 0;
}