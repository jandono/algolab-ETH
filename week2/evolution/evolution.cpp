/*
	Save queries.
	Do DFS traversal on the tree while keeping track of the current path.
	For each node answers all queries for that node by doing binary search on the path.
*/

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int T, n, q, age;
string name, child, parent;
unordered_map<string, int> name_to_index;
unordered_map<int, string> index_to_name;
unordered_map<int, int> index_to_age;
unordered_map<int, vector<pair<int,int> > > queries;
string answers[500001];
vector<int> tree[500001];
bool visited[500001];
vector<int> path;

int binary_search(int age){

	int start = 0, end = path.size()-1, mid = -1;

	while(start <= end){
		mid = start + (end - start)/2;
		int curr_index = path[mid];
		int next_index = path[mid - 1];

		if(index_to_age[curr_index] <= age &&  
			(next_index == 0 || index_to_age[next_index] > age)){

			break;
		}else
		if(index_to_age[curr_index] < age ){
			end = mid - 1;
		}else{
			start = mid + 1;
		}
	}

	return path[mid];
}

void dfs(int curr){

	int n = queries[curr].size();
	for(int i=0;i<n;i++){
		int index = binary_search(queries[curr][i].first);
		answers[queries[curr][i].second] = index_to_name[index];
	}

	for(auto child : tree[curr]){
		path.push_back(child);
		dfs(child);
		path.pop_back();
	}
}

int main(){
	ios_base::sync_with_stdio(false);

	cin >> T;
	for(;T>0;T--){

		cin >> n >> q;
		path.clear();
		queries.clear();
		int root = -1;
		int maxi = -1;
		//specie reading
		for(int i=0;i<n;i++){
			tree[i].clear();

			cin >> name >> age;
			name_to_index[name] = i;
			index_to_name[i] = name;
			index_to_age[i] = age;
			if(age > maxi){
				maxi = age;
				root = i;
			}
		}

		//tree building
		for(int i=0;i<n-1;i++){
			cin >> child >> parent;
			tree[name_to_index[parent]].push_back(name_to_index[child]);
		}
		
		//queries
		for(int i=0;i<q;i++){
			cin >> name >> age;
			queries[name_to_index[name]].push_back(make_pair(age, i));
		}

		path.push_back(root);
		dfs(root);
		path.pop_back();

		for(int i=0;i<q;i++){
			cout << answers[i] << " ";
		}

		cout << "\n";
	}
	return 0;
}