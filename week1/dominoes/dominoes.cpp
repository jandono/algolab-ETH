/*
	Keep track of a running maximum which represents the 
	furthest away point on the line you can hit.
	
	Running time: O(N)
*/

#include <iostream>

using namespace std;

int main(){

	ios_base::sync_with_stdio(false);

	long long T, n;
	cin >> T;
	for(int t=0;t<T;t++){

		cin >> n;
		long long maxi=-1, h;

		for(int i=0;i<n;i++){
			cin >> h;
			if(maxi == -1)
				maxi = h;
			else
			if(h+i > maxi && i<maxi)
				maxi = h+i;
		}
		cout << min(maxi, n) << endl;
	}

	return 0;
}