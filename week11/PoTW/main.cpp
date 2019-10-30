/*
	Bruteforce all possible combinations such that more than n-k players are playing.
	For each combination see if you can split the teams into 2 groups such that the
	sums of skills in each group is equal.

	This approach gives 70 points.
*/

#include <iostream>
#include <bitset>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <assert.h>

typedef long long ll;
int n, k;
ll skill[22], subset_skill[22];
std::vector<ll> first_set, second_set;
std::unordered_map<ll, ll> sums;

void read_test_case(){

	std::cin >> n >> k;
	for(int i=0;i<n;i++)
		std::cin >> skill[i];
}

void solve(){

	ll counter = 0;
	
	ll limit = 1 << n;
	for(int i=0;i<limit;i++){
		std::bitset<22> bits(i);
		if(bits.count() < n-k)
			continue;

		ll s = 0;
		int c = 0;
		for(int j=0;j<n;j++){
			if(i & 1 << j){
				s+=skill[j];
				subset_skill[c++] = skill[j];
			}
		}

		assert(c == bits.count());

		if(s%2 != 0)
			continue;

		ll target_sum = s/2;

		first_set.clear(); second_set.clear();
		for(int ii=0;ii<c;ii++){
			if(ii < c/2)
				first_set.push_back(subset_skill[ii]);
			else
				second_set.push_back(subset_skill[ii]);
		}

		int n_first = first_set.size(), n_second = second_set.size();
		sums.clear();

		ll limit_first = 1 << n_first;
		for(int ii=0;ii<limit_first;ii++){
			ll ss = 0;
			for(int jj=0;jj<n_first;jj++){
				if(ii & 1 << jj)
					ss += first_set[jj];				
			}

			sums[ss]++;
		}

		ll limit_second = 1 << n_second;
		for(int ii=0;ii<limit_second;ii++){
			ll ss = 0;
			for(int jj=0;jj<n_second;jj++){
				if(ii & 1 << jj){
					ss += second_set[jj];
				}
			}

			if(sums.count(target_sum - ss)){
				counter+=sums[target_sum - ss];
			}
		}
	}

	std::cout << counter << std::endl;
}

void test_case(){
	read_test_case();
	solve();
}

int main(){
	std::ios_base::sync_with_stdio(false);

	int T; std::cin >> T; while(T--) test_case();

	return 0;
}