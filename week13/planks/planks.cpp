/*
	Split and list.
	Realise that you need to divide by 24 at the end.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;

ll n, target;
ll planks[20];

void read_testcase(){

	cin >> n;
	target = 0;
	for(int i=0;i<n;i++){
		cin >> planks[i];
		target += planks[i];
	}
}

void all_possibilities(int lbound, int ubound, vi &possibility, vvi &possibilities){

	if(possibility.size() == ubound - lbound){

		vi sums(4, 0);
		for(int i=0;i<possibility.size();i++){
			sums[possibility[i]] += planks[i + lbound];
		}

		possibilities.push_back(sums);
		return;
	}

	for(int i=0;i<4;i++){
		possibility.push_back(i);
		all_possibilities(lbound, ubound, possibility, possibilities);
		possibility.pop_back();
	}
}

void solve_testcase(){

	if(target % 4){
		cout << 0 << endl;
		return;
	}

	target /= 4;

	vi possibility;
	vvi possibilities1, possibilities2;
	all_possibilities(0, n/2, possibility, possibilities1);
	all_possibilities(n/2, n, possibility, possibilities2);

	sort(possibilities2.begin(), possibilities2.end());

	ll counter = 0;
	vi lookup(4);
	for(vi el : possibilities1){

		for(int i=0;i<4;i++)
			lookup[i] = target - el[i];
		
		vvi::iterator low = lower_bound(possibilities2.begin(), possibilities2.end(), lookup);
		vvi::iterator high = upper_bound(possibilities2.begin(), possibilities2.end(), lookup);
		counter += high - low;
	}

	cout << counter / 24 << endl;
}

void testcase(){
	read_testcase();
	solve_testcase();
}

int main(){
	ios_base::sync_with_stdio(false);
	int T; cin >> T; 
	while(T--){
		testcase();
	}
	return 0;
}