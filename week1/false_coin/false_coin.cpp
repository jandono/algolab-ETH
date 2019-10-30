/*
	Basically do set intersections until you find the false coin.
	Add all coins as potential false coins in the beginning.
	Remove good coins from the potentials set.
	If potentials.size() == 1 return false coin, else impossible to deduct.

	Running time: O(K*2pi*logK)
*/

#include <iostream>
#include <set>

using namespace std;

int main(){

	ios_base::sync_with_stdio(false);

	int T, N, K, pi, c;
	cin >> T;

	for(int t=0;t<T;t++){
		cin >> N >> K;

		set<int> potentials, left_coins, right_coins, lesser_coins, greater_coins;

		for(int i=1;i<=N;i++)
			potentials.insert(i);

		for(int k=0;k<K;k++){
			cin >> pi;

			for(int i=0;i<pi;i++){
				cin >> c;
				left_coins.insert(c);
			}

			for(int i=0;i<pi;i++){
				cin >> c;
				right_coins.insert(c);
			}

			char weighting;
			cin >> weighting;

			if(weighting == '='){

				for(auto el : left_coins){
					potentials.erase(el);
				}

				for(auto el : right_coins){
					potentials.erase(el);
				}
			}else{

				for(set<int>::iterator it = potentials.begin(); it != potentials.end();){
					if(!left_coins.count(*it) && !right_coins.count(*it))
						potentials.erase(it++);
					else
						it++;
				}

				if(weighting == '<'){

					for(auto el : left_coins){
						if(greater_coins.count(el)){
							potentials.erase(el);
						}

						lesser_coins.insert(el);
					}

					for(auto el: right_coins){
						if(lesser_coins.count(el)){
							potentials.erase(el);
						}

						greater_coins.insert(el);
					}
				}else{

					for(auto el : right_coins){
						if(greater_coins.count(el)){
							potentials.erase(el);
						}

						lesser_coins.insert(el);
					}

					for(auto el: left_coins){
						if(lesser_coins.count(el)){
							potentials.erase(el);
						}

						greater_coins.insert(el);
					}
				}
			}

			left_coins.clear();
			right_coins.clear();
		}

		if(potentials.size()==1)
			cout << *(potentials.begin()) << endl;
		else
			cout << "0" << endl;
	}

	return 0;
}