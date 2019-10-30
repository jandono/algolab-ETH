/*
	Two pointers/Sliding window approach.
	Move right pointer untill all words are contained.
	Move left pointer while all words are contained.
	Recalculate the minimum.
*/

#include <iostream>
#include <climits>
#include <algorithm>

using namespace std;

int T, m[2050], words_count[2050], n, best, s, e, pos;
vector < pair<int,int> > words;

int main(){
	ios_base::sync_with_stdio(false);

	cin >> T;
	for(;T>0;T--){
		words.clear();

		cin >> n;
		for(int i=0;i<n;i++){
			cin >> m[i];
			words_count[i] = 0;
		}

		for(int i=0;i<n;i++){
			for(int j=0;j<m[i];j++){
				cin >> pos;
				words.push_back(make_pair(pos, i));
			}
		}

		sort(words.begin(), words.end());

		s = 0;
		e = 0;
		best = INT_MAX;
		int counter = 0;
		while(true){

			while(counter < n && e < words.size()){

				if(words_count[words[e].second]==0)
					counter++;

				words_count[words[e].second]++;
				e++;
			}

			while(counter == n && s <= e){

				if(words_count[words[s].second]==1)
					counter--;

				words_count[words[s].second]--;
				s++;
			}

			best = min(best, words[e-1].first - words[s-1].first + 1);

			if(e == words.size() && counter < n)
				break;
		}

		cout << best << endl;
	}

	return 0;
}