/*
	Assign heavy boxes to stronger people first.
	Simulate until no person can lift the lightest box. 
*/


#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

int main(){

	ios_base::sync_with_stdio(false);

	int T, n, m, strengths[300010], box;

	cin >> T;

	for(;T>0;T--){
		cin >> n >> m;
		multiset<int, greater<int> > boxes;

		for(int i=0;i<n;i++)
			cin >> strengths[i];

		for(int i=0;i<m;i++){
			cin >> box;
			boxes.insert(box);
		}

		sort(strengths, strengths + n, greater<int>());

		int box_count = 0;
		int counter = 0;

		int i;

		while(box_count != m){

			i=0;
			bool flag = false;
			for(set<int>::iterator b = boxes.begin(); b != boxes.end();){
				
				set<int>::iterator current = b++;

				if(strengths[i] < *boxes.rbegin() || i==n){
					break;
				}
					
				if(strengths[i] >= *current){
					box_count++;
					i++;
					boxes.erase(current);
					flag = true;
				}			
			}
			
			if(flag)
				counter++;

			if(i==0){
				break;
			}
		}

		if(box_count == m)
			cout << 3*counter - 1 << endl;
		else
			cout << "impossible" << endl;
	}

	return 0;
}