/*
	Greedy.
	Take next available with smallest right coordinate.
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>

using namespace std;

int main(){

	ios_base::sync_with_stdio(false);

	int T, l, p, n;
	vector< pair<int, int> > boats;
	cin >> T;

	int maxi = -1;
	for(;T>0;T--){

		cin >> n;
		boats.clear();
		for(int i=0;i<n;i++){
			cin >> l >> p;
			boats.push_back(make_pair(p, l));
			maxi = max(p + l, maxi);
		}

		sort(boats.begin(), boats.end());

		int right_most = boats[0].first;
		int prev_right = right_most - boats[0].second;
		int counter = 1;

		for(int i=1;i<boats.size();i++){

			int right_position = boats[i].first;
			int left_position = boats[i].first - boats[i].second;

			if(right_position >= right_most){
				prev_right = right_most;
				right_most = max(right_position, right_most + boats[i].second);
				counter++;
			}
			else{
				right_position = max(right_position, prev_right + boats[i].second);
				right_most = min(right_most, right_position);
			}
		}	

		cout << counter << endl;
	}

	return 0;
}