/*
	Use BFS to get connected components.
	Combine it with binary search.

	This approach gets me 75 points.
	I think that Union Find is needed for 100 points.
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> ii;

ii planets[30001];
ll x, y, n, r;
vector<int> graph[30001];


void read_test_case(){

	cin >> n >> r;
	r*=r;
	for(int i=0;i<n;i++){
		cin >> x >> y;
		planets[i] = {x, y};
		graph[i].clear();
	}
}

void build_graph(){

	for(int i=0;i<n;i++){
		for(int j=i+1;j<n;j++){
			ll dist = (planets[i].first - planets[j].first) * (planets[i].first - planets[j].first) + (planets[i].second - planets[j].second) * (planets[i].second - planets[j].second);
			if(dist <= r){
				graph[i].push_back(j);
				graph[j].push_back(i);
			}
		}
	}
}

int bfs(int k){

	unordered_set<int> potentials;
	for(int i=k;i<n;i++){
		potentials.insert(i);
	}

	int max_counter = 0;

	while(!potentials.empty()){
		queue<int> q;
		q.push(*potentials.begin());
		int counter = 0; 
		while(!q.empty()){
			int curr = q.front(); q.pop();
			potentials.erase(curr);

			counter++;

			if(counter == k)
				return k;

			for(auto neighbor : graph[curr]){
				if(potentials.count(neighbor)){
					potentials.erase(neighbor);
					q.push(neighbor);
				}
			}
		}

		if(counter > max_counter){
			max_counter = counter;
		}

		if(potentials.size() <= max_counter)
			return max_counter;
	}
}

void solve(){

	int k, s = 0, e = n, curr_solution;
	int best_solution = 0, best_k = -1;

	while(s < e){
		k = s + (e-s)/2;
		curr_solution = min(bfs(k), k);
		if(curr_solution==k){
			if(k > best_k)
				best_k = k;
		}
		if(curr_solution < k){
			e = k;
		}else{
			s = k+1;
		}
	}

	cout << best_k << endl;
}

void test_case(){
	read_test_case();
	build_graph();
	solve();
}

int main(){
	int T;
	std::cin >> T;

	while(T--) test_case();
}